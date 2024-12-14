#include <cppack/cppack.hpp>

#include <utility/vector.hpp>
#include <project/project_exceptions.hpp>
#include <make/make_generator.hpp>



const fs::path CPPack::cppackDirectoryPath = getHomeDirectoryPath().append(".cppack");
const fs::path CPPack::cppackIndexDirectoryPath = CPPack::cppackDirectoryPath / "index";





void CPPack::init() noexcept
{
	setupCppackGlobalEnvironment();
}





bool CPPack::directoryContainsProjectFile(const std::string& path, fs::path* const projectFilePath) noexcept
{
	for (const auto& file : fs::directory_iterator(path))
	{
		if (file.path().extension() != Project::projectFileExtension)
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

	ProjectDataManager::writeToFile(data, data.name + Project::projectFileExtension);
}


void CPPack::setupCppackGlobalEnvironment() noexcept
{
	createDirectoryIfNotExists(cppackDirectoryPath);
	createDirectoryIfNotExists(cppackIndexDirectoryPath);
}
