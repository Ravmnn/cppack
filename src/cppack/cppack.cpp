#include <cctype>
#include <cppack/cppack.hpp>

#include <utility/file.hpp>
#include <utility/vector.hpp>
#include <project_data/project_data_exceptions.hpp>
#include <make/make_generator.hpp>
#include <make/compiler_options.hpp>
#include <cppack/cppack_exceptions.hpp>



const fs::path CPPack::cppackDirectoryPath = getHomeDirectoryPath().append(".cppack");
const fs::path CPPack::cppackIndexDirectoryPath = CPPack::cppackDirectoryPath / "index";

const std::string CPPack::projectFileExtension = ".cpproj";
const std::string CPPack::buildMakefileName = "Makefile";





CPPack::CPPack(const std::string& path)
{
	if (!fs::exists(path))
		throw InvalidProjectHandlingException("Invalid path: " + path);

	_hasProjectFilePath = directoryHierarchyContainsProjectFile(path, &_projectFilePath);
}





std::string CPPack::getBuildMakefilePath() const noexcept
{
	return toAbsolutePath((fs::path)getData().buildDirectory / buildMakefileName);
}





std::string CPPack::getProjectOutFileExtension() const noexcept
{
	switch (getData().type)
	{
		case ProjectType::SharedLibrary: return ".so";
		case ProjectType::StaticLibrary: return ".a";

		default: return "";
	}
}


std::string CPPack::getProjectOutFileStem() const noexcept
{
	const ProjectData data = getData();

	switch (data.type)
	{
		case ProjectType::SharedLibrary:
		case ProjectType::StaticLibrary:
			return "lib" + data.name;

		default:
			return data.name;
	}
}


std::string CPPack::getProjectFullOutFileName() const noexcept
{
	return getProjectOutFileStem() + getProjectOutFileExtension();
}





void CPPack::buildProject() const
{
	const ProjectData projectData = getData();

	createDirectoryIfNotExists(toAbsolutePath(projectData.buildDirectory));
	generateMakefileFromProject(getBuildMakefilePath(), *this);

	buildProjectDependencies();

	runProjectMakefile("build");
}


void CPPack::buildProjectDependencies() const
{
	for (const std::string& dependency : getData().dependencies)
		getPackage(dependency).buildProject();
}


void CPPack::runProject() const
{
	if (getData().type != ProjectType::Executable)
		throw InvalidProjectHandlingException("Project type is not runnable");

	buildProject();
	runProjectMakefile("run");
}


void CPPack::cleanProject() const
{
	fs::remove_all(getData().buildDirectory);
}


void CPPack::runProjectMakefile(const std::string& makeRule) const
{
	const std::string path = getBuildMakefilePath();
	const std::string command = "make " + makeRule + " -s -f " + path;

	if (!fs::exists(path))
		throw InvalidProjectHandlingException("Could not find Makefile: " + path);

	system(command.c_str());
}





void CPPack::addPackageDependency(const std::string& name) const
{
	InvalidPackageIndexHandling::throwIfNotRegistered(name);
	InvalidPackageIndexHandling::throwIfIsDependency(*this, name);

	ProjectData projectData = getData();
	projectData.dependencies.push_back(name);

	ProjectDataManager::writeToFile(projectData, getProjectFilePath());
}


void CPPack::removePackageDependency(const std::string& name) const
{
	InvalidPackageIndexHandling::throwIfIsNotDependency(*this, name);

	ProjectData data = getData();
	data.dependencies.erase(find(data.dependencies, name));

	ProjectDataManager::writeToFile(data, getProjectFilePath());
}


bool CPPack::isPackageADependency(const std::string& name) const noexcept
{
	const ProjectData data = getData();
	return find(data.dependencies, name) != data.dependencies.cend();
}





std::vector<std::string> CPPack::getIncludePaths(bool includeProject) const noexcept
{
	const ProjectData data = getData();

	std::vector<std::string> includePaths;
	std::vector<std::string> additionalPaths;

	for (const std::string& path : data.additionalIncludePaths)
		additionalPaths.push_back(toAbsolutePath(path));

	if (includeProject)
		includePaths.push_back(getFullHeaderPath());

	insertAtEnd(includePaths, additionalPaths);

	return includePaths;
}


std::vector<std::string> CPPack::getLibraryPaths(bool includeProject) const noexcept
{
	const ProjectData data = getData();

	std::vector<std::string> libraryPaths;
	// std::vector<std::string> additionalPaths;

	// for (const std::string& path : data.additionalIncludePaths)
	// 	additionalPaths.push_back(toAbsolutePath(path));

	if (includeProject)
		libraryPaths.push_back(getFullSourcePath());

	// insertAtEnd(libraryPaths, additionalPaths);

	return libraryPaths;
}


std::vector<std::string> CPPack::getDependenciesIncludePaths() const noexcept
{
	const ProjectData data = getData();

	std::vector<std::string> includePaths;

	for (const std::string& dependency : data.dependencies)
	{
		const CPPack package = getPackage(dependency);

		insertAtEnd(includePaths, package.getIncludePaths());
		insertAtEnd(includePaths, package.getDependenciesIncludePaths());
	}

	return includePaths;
}


std::vector<std::string> CPPack::getDependenciesLibraryPaths() const noexcept
{
	const ProjectData data = getData();

	std::vector<std::string> libraryPaths;

	for (const std::string& dependency : data.dependencies)
	{
		CPPack package = getPackage(dependency);

		libraryPaths.push_back(package.getFullBuildPath());
		insertAtEnd(libraryPaths, package.getDependenciesLibraryPaths());
	}

	return libraryPaths;
}


std::vector<std::string> CPPack::getAllIncludePaths() const noexcept
{
	std::vector<std::string> includePaths;

	insertAtEnd(includePaths, getIncludePaths());
	insertAtEnd(includePaths, getDependenciesIncludePaths());

	return includePaths;
}


std::vector<std::string> CPPack::getAllLibraryPaths() const noexcept
{
	std::vector<std::string> libraryPaths;

	// no need to include the project out library
	insertAtEnd(libraryPaths, getLibraryPaths(false));
	insertAtEnd(libraryPaths, getDependenciesLibraryPaths());

	return libraryPaths;
}





std::string CPPack::getFullBuildPath() const noexcept
{
	const ProjectData data = getData();
	return toAbsolutePath(data.buildDirectory) / data.currentBuildSetting;
}


std::string CPPack::getFullHeaderPath() const noexcept
{
	return toAbsolutePath(getData().headerDirectory);
}


std::string CPPack::getFullSourcePath() const noexcept
{
	return toAbsolutePath(getData().sourceDirectory);
}







void CPPack::init() noexcept
{
	setupCppackGlobalEnvironment();
}





static void copyPackageToGlobalPackageIndex(const CPPack& package)
{
	const fs::path packagePath = fs::absolute(package.getProjectFilePath()).parent_path();
	const fs::path targetPath = CPPack::cppackIndexDirectoryPath / package.getData().name;

	fs::create_directory(targetPath);

	fs::copy(packagePath, targetPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}



void CPPack::registerPackage(const CPPack& package)
{
	const ProjectData& packageData = package.getData();

	InvalidPackageIndexHandling::throwIfRegistered(packageData.name);

	if (packageData.type == ProjectType::Executable)
		throw InvalidPackageIndexHandling("Cannot register a executable type package");

	copyPackageToGlobalPackageIndex(package);
}


void CPPack::unregisterPackage(const std::string& name)
{
	InvalidPackageIndexHandling::throwIfNotRegistered(name);

	fs::remove_all(cppackIndexDirectoryPath / name);
}


bool CPPack::isPackageRegistered(const std::string& name) noexcept
{
	for (const auto& dir : fs::directory_iterator(cppackIndexDirectoryPath))
		if (dir.path().stem().string() == name)
			return true;

	return false;
}





bool CPPack::directoryContainsProjectFile(const std::string& path, fs::path* const projectFilePath) noexcept
{
	for (const auto& file : fs::directory_iterator(path))
	{
		if (file.path().extension() != projectFileExtension)
			continue;

		if (projectFilePath)
			*projectFilePath = file.path();

		return true;
	}

	return false;
}


bool CPPack::directoryHierarchyContainsProjectFile(const std::string& path, fs::path* const projectFilePath) noexcept
{
	const fs::path ppath = path;

	if (directoryContainsProjectFile(ppath, projectFilePath))
		return true;

	return ppath != ppath.root_path() ? directoryHierarchyContainsProjectFile(ppath.parent_path(), projectFilePath) : false;
}





ProjectData CPPack::generateDefaultProjectData(const std::string& name, const ProjectType type) noexcept
{
	ProjectData data;

	data.name = (name.empty() ? fs::current_path().stem().string() : name);
	data.type = type;
	data.sourceDirectory = "src";
	data.headerDirectory = (type == ProjectType::Executable ? data.sourceDirectory : "include");
	data.buildDirectory = "build";
	data.currentBuildSetting = "debug";
	data.languageCompiler = "clang++";
	data.languageVersion = 20,
	data.buildSettings = {
		generateDefaultBuildSetting("debug", BuildOptimizationType::Debug, BuildWarningType::All),
		generateDefaultBuildSetting("release", BuildOptimizationType::High, BuildWarningType::None)
	};

	return data;
}


BuildSetting CPPack::generateDefaultBuildSetting(const std::string& name, const BuildOptimizationType optimization, const BuildWarningType warning) noexcept
{
	BuildSetting setting;

	setting.name = name;
	setting.optimizationType = optimization;
	setting.warningType = warning;

	return setting;
}





void CPPack::setupProjectEnvironment(const ProjectData& data) noexcept
{
	createDirectoryIfNotExists(data.sourceDirectory);
	createDirectoryIfNotExists(data.headerDirectory);

	ProjectDataManager::writeToFile(data, data.name + CPPack::projectFileExtension);
}


void CPPack::setupCppackGlobalEnvironment() noexcept
{
	createDirectoryIfNotExists(cppackDirectoryPath);
	createDirectoryIfNotExists(cppackIndexDirectoryPath);
}
