#include <cppack/cppack.hpp>

#include <utility/file.hpp>



const std::string CPPack::projectFileExtension = ".cpproj";


std::string CPPack::projectFilePath = "";
bool CPPack::hasProjectFilePath = false;





void CPPack::init(const std::string& path) noexcept
{
	hasProjectFilePath = directoryHierarchyContainsProjectFile(path, &projectFilePath);
}





bool CPPack::directoryContainsProjectFile(const std::string& path, std::string* const projectFilePath) noexcept
{
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().extension() != projectFileExtension)
			continue;

		if (projectFilePath)
			*projectFilePath = file.path();

		return true;
	}

	return false;
}


bool CPPack::directoryHierarchyContainsProjectFile(const std::string& path, std::string* const projectFilePath) noexcept
{
	const std::filesystem::path ppath = path;

	if (directoryContainsProjectFile(ppath, projectFilePath))
		return true;

	return ppath != ppath.root_path() ? directoryHierarchyContainsProjectFile(ppath.parent_path(), projectFilePath) : false;
}





ProjectData CPPack::generateDefaultProjectData(const std::string& name, const ProjectType type) noexcept
{
	ProjectData data;

	data.name = name;
	data.type = type;
	data.sourceDirectory = "src";
	data.headerDirectory = (type == ProjectType::Executable ? data.sourceDirectory : "include");
	data.buildDirectory = "build";
	data.currentBuildSetting = "debug";
	data.languageCompiler = "clang++";
	data.languageVersion = 17,
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
	createDirectoryIfNotExists(data.buildDirectory);

	ProjectDataManager(data).writeToFile(data.name + CPPack::projectFileExtension);
}
