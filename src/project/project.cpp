#include <project/project.hpp>

#include <filesystem>

#include <utility/vector.hpp>
#include <package/global_index.hpp>
#include <project/project_data.hpp>
#include <project/project_exceptions.hpp>
#include <cppack/cppack.hpp>
#include <make/make_generator.hpp>



const std::string Project::projectFileExtension = ".cpproj";
const std::string Project::makefileName = "Makefile";



Project::Project(const std::string& path)
{
	if (!fs::exists(path))
		throw InvalidProjectHandlingException("Invalid path: " + path);

	_hasProjectFilePath = CPPack::directoryHierarchyContainsProjectFile(path, &_projectFilePath);
}





std::string Project::getProjectOutFileExtension() const noexcept
{
	switch (getData().type)
	{
		case ProjectType::SharedLibrary: return ".so";
		case ProjectType::StaticLibrary: return ".a";

		default: return "";
	}
}


std::string Project::getProjectOutFileStem() const noexcept
{
	const ProjectData projectData = getData();

	switch (projectData.type)
	{
		case ProjectType::SharedLibrary:
		case ProjectType::StaticLibrary:
			return "lib" + projectData.name;

		default:
			return projectData.name;
	}
}


std::string Project::getProjectFullOutFileName() const noexcept
{
	return getProjectOutFileStem() + getProjectOutFileExtension();
}





void Project::buildProject() const
{
	createDirectoryIfNotExists(getBuildPath());
	generateMakefileFromProject(getMakefilePath(), *this);

	buildProjectDependencies();

	runProjectMakefile("build");
}


void Project::buildProjectDependencies() const
{
	for (const std::string& dependency : getData().dependencies)
		GlobalPackageIndex::getPackage(dependency).buildProject();
}


void Project::runProject() const
{
	if (getData().type != ProjectType::Executable)
		throw InvalidProjectHandlingException("Project type is not runnable");

	buildProject();
	runProjectMakefile("run");
}


void Project::cleanProject() const
{
	fs::remove_all(getData().buildDirectory);
}


void Project::runProjectMakefile(const std::string& makeRule) const
{
	const std::string path = getMakefilePath();
	const std::string command = "make " + makeRule + " -s -f " + path;

	if (!fs::exists(path))
		throw InvalidProjectHandlingException("Could not find Makefile: " + path);

	system(command.c_str());
}


void Project::makefyProject() const
{
	generateIndependentMakefilesFromBuildSettings("mkfiles", *this);
	generateIndependentMakefileFromProject(getIndependentMakefilePath(), *this);
}





void Project::addPackageDependency(const std::string& name) const
{
	InvalidPackageIndexHandling::throwIfNotRegistered(name);
	InvalidPackageIndexHandling::throwIfIsDependency(*this, name);

	ProjectData projectData = getData();
	projectData.dependencies.push_back(name);

	ProjectDataManager::writeToFile(projectData, getAbsoluteProjectFilePath());
}


void Project::removePackageDependency(const std::string& name) const
{
	InvalidPackageIndexHandling::throwIfIsNotDependency(*this, name);

	ProjectData projectData = getData();
	projectData.dependencies.erase(find(projectData.dependencies, name));

	ProjectDataManager::writeToFile(projectData, getAbsoluteProjectFilePath());
}


bool Project::isPackageADependency(const std::string& name) const noexcept
{
	const ProjectData projectData = getData();
	return find(projectData.dependencies, name) != projectData.dependencies.cend();
}





std::vector<std::string> Project::getIncludePaths(const bool includeProject, const bool absolutePaths) const noexcept
{
	std::vector<std::string> includePaths;
	std::vector<std::string> additionalPaths;

	for (const std::string& path : getData().additionalIncludePaths)
		additionalPaths.push_back(absolutePaths ? toAbsoluteProjectPath(path).string() : path);

	if (includeProject)
		includePaths.push_back(getHeaderPath(absolutePaths));

	insertAtEnd(includePaths, additionalPaths);

	return includePaths;
}


std::vector<std::string> Project::getLibraryPaths(const bool includeProject, const bool absolutePaths) const noexcept
{
	std::vector<std::string> libraryPaths;
	std::vector<std::string> additionalPaths;

	for (const std::string& path : getData().additionalLibraryPaths)
		additionalPaths.push_back(absolutePaths ? toAbsoluteProjectPath(path).string() : path);

	if (includeProject)
		libraryPaths.push_back(getSourcePath(absolutePaths));

	insertAtEnd(libraryPaths, additionalPaths);

	return libraryPaths;
}


std::vector<std::string> Project::getLibraries() const noexcept
{
	const ProjectData projectData = getData();

	std::vector<std::string> libraries;

	insertAtEnd(libraries, projectData.dependencies);
	insertAtEnd(libraries, projectData.additionalLibraries);

	return libraries;
}


std::vector<std::string> Project::getDependenciesIncludePaths() const noexcept
{
	std::vector<std::string> includePaths;

	for (const std::string& dependency : getData().dependencies)
	{
		const Project package = GlobalPackageIndex::getPackage(dependency);

		insertAtEnd(includePaths, package.getIncludePaths());
		insertAtEnd(includePaths, package.getDependenciesIncludePaths());
	}

	return includePaths;
}


std::vector<std::string> Project::getDependenciesLibraryPaths() const noexcept
{
	std::vector<std::string> libraryPaths;

	for (const std::string& dependency : getData().dependencies)
	{
		const Project package = GlobalPackageIndex::getPackage(dependency);

		insertAtEnd(libraryPaths, package.getLibraryPaths());
		insertAtEnd(libraryPaths, package.getDependenciesLibraryPaths());
	}

	return libraryPaths;
}


std::vector<std::string> Project::getDependenciesLibraries() const noexcept
{
	std::vector<std::string> libraries;

	for (const std::string& dependency : getData().dependencies)
	{
		const Project package = GlobalPackageIndex::getPackage(dependency);

		insertAtEnd(libraries, package.getLibraries());
		insertAtEnd(libraries, package.getDependenciesLibraries());
	}

	return libraries;
}


std::vector<std::string> Project::getAllIncludePaths(const bool absolutePaths) const noexcept
{
	std::vector<std::string> includePaths;

	insertAtEnd(includePaths, getIncludePaths(true, absolutePaths));
	insertAtEnd(includePaths, getDependenciesIncludePaths());

	return includePaths;
}


std::vector<std::string> Project::getAllLibraryPaths(const bool absolutePaths) const noexcept
{
	std::vector<std::string> libraryPaths;

	// no need to include the project out library
	insertAtEnd(libraryPaths, getLibraryPaths(false, absolutePaths));
	insertAtEnd(libraryPaths, getDependenciesLibraryPaths());

	return libraryPaths;
}


std::vector<std::string> Project::getAllLibraries() const noexcept
{
	std::vector<std::string> libraries;

	insertAtEnd(libraries, getLibraries());
	insertAtEnd(libraries, getDependenciesLibraries());

	return libraries;
}





fs::path Project::getMakefilePath(const bool absolutePath) const noexcept
{
	return getBuildPath(absolutePath) / makefileName;
}


fs::path Project::getIndependentMakefilePath(const bool absolutePath) const noexcept
{
	return absolutePath ? getAbsoluteProjectPath() / makefileName : fs::path(makefileName);
}



fs::path Project::getBuildPath(const bool absolutePath) const noexcept
{
	const ProjectData data = getData();
	return absolutePath ? getAbsoluteProjectPath() / data.buildDirectory : fs::path(data.buildDirectory);
}


fs::path Project::getFinalBuildPath(const bool absolutePath) const noexcept
{
	const ProjectData data = getData();
	const fs::path relativeFinalBuildPath = fs::path(data.buildDirectory) / data.currentBuildSetting;

	return absolutePath ? getAbsoluteProjectPath() / relativeFinalBuildPath : relativeFinalBuildPath;
}


fs::path Project::getHeaderPath(const bool absolutePath) const noexcept
{
	const ProjectData data = getData();
	return absolutePath ? getAbsoluteProjectPath() / data.headerDirectory : fs::path(data.headerDirectory);
}


fs::path Project::getSourcePath(const bool absolutePath) const noexcept
{
	const ProjectData data = getData();
	return absolutePath ? getAbsoluteProjectPath() / data.sourceDirectory : fs::path(data.sourceDirectory);
}
