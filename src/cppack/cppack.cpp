#include <cppack/cppack.hpp>

#include <utility/file.hpp>
#include <project_data/project_data_exceptions.hpp>
#include <make/make_generator.hpp>
#include <make/compiler_options.hpp>



const std::string CPPack::projectFileExtension = ".cpproj";
const std::string CPPack::buildMakefileName = "Makefile";


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





std::string CPPack::getBuildMakefilePath(const ProjectData& data) noexcept
{
	return std::filesystem::path(data.buildDirectory).append(buildMakefileName);
}


void CPPack::setupProjectEnvironment(const ProjectData& data) noexcept
{
	createDirectoryIfNotExists(data.sourceDirectory);
	createDirectoryIfNotExists(data.headerDirectory);

	ProjectDataManager(data).writeToFile(data.name + CPPack::projectFileExtension);
}


void CPPack::buildProject(const ProjectData& data)
{
	createDirectoryIfNotExists(data.buildDirectory);

	generateMakefileFromProjectData(getBuildMakefilePath(data), data);
}





void CPPack::generateMakefileFromProjectData(const std::string& fileToSave, const ProjectData& data)
{
	const BuildSetting* buildSetting = data.buildSetting();

	if (!buildSetting)
		throw InvalidProjectDataException("There are no build settings");


	std::vector<std::string> include_paths = data.additionalIncludePaths;
	include_paths.insert(include_paths.begin(), data.headerDirectory);


	MakefileGenerator make;

	make.comment("This was auto-generated");
	make.newline();

	make.variable("NAME", data.name);
	make.newline();

	make.variable("CURRENT_BUILD_SETTING", data.currentBuildSetting);
	make.newline();

	make.variable("SOURCE_PATH", data.sourceDirectory);
	make.listVariableWithPrefix("INCLUDE_PATHS", "-I", include_paths);
	make.variable("BUILD_PATH", data.buildDirectory);
	make.newline();

	make.variable("COMPLETE_BUILD_PATH", "$(BUILD_PATH)/$(CURRENT_BUILD_SETTING)");
	make.variable("OBJECT_PATH", "$(COMPLETE_BUILD_PATH)/obj");
	make.newline();

	make.variable("BIN_PATH", "$(COMPLETE_BUILD_PATH)/$(NAME)");
	make.newline();

	make.variable("SOURCES", "$(shell find $(SOURCE_PATH) -name \"*.cpp\")");
	make.variable("OBJECTS", "$(addprefix $(OBJECT_PATH)/, $(patsubst $(SOURCE_PATH)/%, %, $(SOURCES:.cpp=.o)))");
	make.newline();

	make.variable("CPP_COMPILER", data.languageCompiler);
	make.variable("CPP_VERSION", std::to_string(data.languageVersion));
	make.newline();

	make.variable("CPP_OPTIMIZATION", buildOptimizationTypeToCompilerOption(buildSetting->optimizationType));
	make.variable("CPP_WARNING", buildWarningTypeToCompilerOption(buildSetting->warningType));
	make.listVariableWithPrefix("CPP_DEFINES", "-D", buildSetting->defines);
	make.variable("CPP_ADDITIONAL_OPTIONS", buildSetting->additionalOptions);
	make.newline();

	make.variable("CPP_OPTIONS", "$(CPP_VERSION) $(CPP_OPTIMIZATION) $(CPP_WARNING) $(CPP_DEFINES) $(CPP_ADDITIONAL_OPTIONS)");

	writeFile(fileToSave, make.get());
}
