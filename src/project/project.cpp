#include <project/project.hpp>

#include <filesystem>

#include <utility/vector.hpp>
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

	runProjectMakefile("build");
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





std::vector<std::string> Project::getPaths(const std::string& main, const std::vector<std::string>& additional,
	const bool includeProject, const bool absolutePaths) const noexcept
{
	std::vector<std::string> includePaths;
	std::vector<std::string> additionalPaths;

	for (const std::string& path : additional)
		additionalPaths.push_back(absolutePaths ? toAbsoluteProjectPath(path).string() : path);

	if (includeProject)
		includePaths.push_back(main);

	insertAtEnd(includePaths, additionalPaths);

	return includePaths;
}


std::vector<std::string> Project::getIncludePaths(const bool includeProject, const bool absolutePaths) const noexcept
{
	return getPaths(getHeaderPath(absolutePaths), getData().additionalIncludePaths, includeProject, absolutePaths);
}


std::vector<std::string> Project::getLibraryPaths(const bool includeProject, const bool absolutePaths) const noexcept
{
	return getPaths(getSourcePath(absolutePaths), getData().additionalLibraryPaths, includeProject, absolutePaths);
}


std::vector<std::string> Project::getLibraries() const noexcept
{
	const ProjectData projectData = getData();

	std::vector<std::string> libraries;

	insertAtEnd(libraries, projectData.additionalLibraries);

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
