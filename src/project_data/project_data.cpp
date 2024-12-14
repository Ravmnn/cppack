#include <project_data/project_data.hpp>

#include <iostream>

#include <utility/vector.hpp>



std::string buildOptimizationTypeToString(const BuildOptimizationType type) noexcept
{
    switch (type)
    {
        case BuildOptimizationType::None:          return "none";
        case BuildOptimizationType::Low:           return "low";
        case BuildOptimizationType::Medium:        return "medium";
        case BuildOptimizationType::High:          return "high";
        case BuildOptimizationType::Extreme:       return "extreme";
        case BuildOptimizationType::Shrink:        return "shrink";
        case BuildOptimizationType::ExtremeShrink: return "extreme_shrink";
        case BuildOptimizationType::Debug:         return "debug";

        default: return "invalid";
    }
}


BuildOptimizationType buildOptimizationTypeFromString(const std::string& source) noexcept
{
    if (source == "none")           return BuildOptimizationType::None;
    if (source == "low")            return BuildOptimizationType::Low;
    if (source == "medium")         return BuildOptimizationType::Medium;
    if (source == "high")           return BuildOptimizationType::High;
    if (source == "extreme")        return BuildOptimizationType::Extreme;
    if (source == "shrink")         return BuildOptimizationType::Shrink;
    if (source == "extreme_shrink") return BuildOptimizationType::ExtremeShrink;
    if (source == "debug")          return BuildOptimizationType::Debug;

    return BuildOptimizationType::None;
}


bool isBuildOptimizationStringValid(const std::string& source) noexcept
{
	return buildOptimizationTypeFromString(source) != BuildOptimizationType::Invalid;
}





std::string buildWarningTypeToString(const BuildWarningType type) noexcept
{
    switch (type)
    {
        case BuildWarningType::None:   return "none";
        case BuildWarningType::Normal: return "normal";
        case BuildWarningType::All:    return "all";
        case BuildWarningType::Extra:  return "extra";

        default: return "invalid";
    }
}


BuildWarningType buildWarningTypeFromString(const std::string& source) noexcept
{
    if (source == "none")   return BuildWarningType::None;
    if (source == "normal") return BuildWarningType::Normal;
    if (source == "all")    return BuildWarningType::All;
    if (source == "extra")  return BuildWarningType::Extra;

    return BuildWarningType::None;
}


bool isBuildWarningTypeStringValid(const std::string& source) noexcept
{
	return buildWarningTypeFromString(source) != BuildWarningType::Invalid;
}





std::string projectTypeToString(const ProjectType type) noexcept
{
    switch (type)
    {
        case ProjectType::Executable: return "executable";
        case ProjectType::StaticLibrary: return "static-library";
        case ProjectType::SharedLibrary: return "shared-library";

        default: return "invalid";
    }
}


ProjectType projectTypeFromString(const std::string& source) noexcept
{
    if (source == "executable") return ProjectType::Executable;
	if (source == "static-library") return ProjectType::StaticLibrary;
	if (source == "shared-library") return ProjectType::SharedLibrary;

    return ProjectType::Executable;
}


bool isProjectTypeStringValid(const std::string& source) noexcept
{
	return projectTypeFromString(source) != ProjectType::Invalid;
}





const JsonPropertyValidationRequirements BuildSetting::prop_name = { "name", json::value_t::string };
const JsonPropertyValidationRequirements BuildSetting::prop_optimizationType = { "optimization", json::value_t::string };
const JsonPropertyValidationRequirements BuildSetting::prop_warningType = {  "warning", json::value_t::string };
const JsonPropertyValidationRequirements BuildSetting::prop_defines = { "defines", json::value_t::array, json::value_t::string };
const JsonPropertyValidationRequirements BuildSetting::prop_additionalOptions = { "additional_options", json::value_t::string };



BuildSetting::BuildSetting(const json& jsonData)
	: JsonPropertiesValidator({
		prop_name, prop_optimizationType, prop_warningType, prop_defines,
		prop_additionalOptions
	})
{
	fromJson(jsonData);
}


BuildSetting::BuildSetting() : JsonPropertiesValidator()
{}



void BuildSetting::fromJson(const json& jsonData)
{
	validateProperties(jsonData);

    name = jsonData[prop_name.name];
    optimizationType = buildOptimizationTypeFromString(jsonData[prop_optimizationType.name]);
    warningType = buildWarningTypeFromString(jsonData[prop_warningType.name]);
    defines = convertJsonStringArrayToVector(jsonData[prop_defines.name]);
    additionalOptions = jsonData[prop_additionalOptions.name];
}


json BuildSetting::toJson() const noexcept
{
	return {
		{ prop_name.name, name },
		{ prop_optimizationType.name, buildOptimizationTypeToString(optimizationType) },
		{ prop_warningType.name, buildWarningTypeToString(warningType) },
		{ prop_defines.name, defines },
		{ prop_additionalOptions.name, additionalOptions }
	};
}



json BuildSetting::toJsonArray(const std::vector<BuildSetting>& data) noexcept
{
	json jsonData = json::array();

	for (size_t i = 0; i < data.size(); i++)
		jsonData[i] = data[i].toJson();

	return jsonData;
}


std::vector<BuildSetting> BuildSetting::vectorFromJson(const json& jsonData)
{
    std::vector<BuildSetting> buildSettings;

    for (const auto& item : jsonData)
        buildSettings.push_back(BuildSetting(item));

    return buildSettings;
}


std::vector<std::string> BuildSetting::getBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept
{
    std::vector<std::string> names;

    for (const BuildSetting& setting : settings)
        names.push_back(setting.name);

    return names;
}





const JsonPropertyValidationRequirements ProjectData::prop_name = { "name", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_type = { "type", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_dependencies = { "dependencies", json::value_t::array, json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_sourceDirectory = { "source_directory", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_headerDirectory = { "header_directory", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_buildDirectory = { "build_directory", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_additionalIncludePaths = { "additional_include_paths", json::value_t::array, json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_additionalLibraryPaths = { "additional_library_paths", json::value_t::array, json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_additionalLibraries = { "additional_libraries", json::value_t::array, json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_languageCompiler = { "language_compiler", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_languageVersion = { "language_version", json::value_t::number_unsigned };
const JsonPropertyValidationRequirements ProjectData::prop_currentBuildSetting = { "current_build_setting", json::value_t::string };
const JsonPropertyValidationRequirements ProjectData::prop_buildSettings = { "build_settings", json::value_t::array, json::value_t::object };



ProjectData::ProjectData(const json& jsonData)
	: JsonPropertiesValidator({
		prop_name, prop_type, prop_dependencies, prop_sourceDirectory,
		prop_headerDirectory, prop_buildDirectory, prop_additionalIncludePaths, prop_additionalLibraryPaths,
		prop_additionalLibraries, prop_languageCompiler, prop_languageVersion, prop_currentBuildSetting, prop_buildSettings
	})
{
	fromJson(jsonData);
}


ProjectData::ProjectData() : JsonPropertiesValidator()
{}



const BuildSetting* ProjectData::buildSetting() const noexcept
{
	for (const BuildSetting& setting : buildSettings)
		if (setting.name == currentBuildSetting)
			return &setting;

	return nullptr;
}



void ProjectData::fromJson(const json& jsonData)
{
	validateProperties(jsonData);

    name = jsonData[prop_name.name];
    type = projectTypeFromString(jsonData[prop_type.name]);
    dependencies = convertJsonStringArrayToVector(jsonData[prop_dependencies.name]);
    sourceDirectory = jsonData[prop_sourceDirectory.name];
    headerDirectory = jsonData[prop_headerDirectory.name];
    buildDirectory = jsonData[prop_buildDirectory.name];
    additionalIncludePaths = convertJsonStringArrayToVector(jsonData[prop_additionalIncludePaths.name]);
    additionalLibraryPaths = convertJsonStringArrayToVector(jsonData[prop_additionalLibraryPaths.name]);
    additionalLibraries = convertJsonStringArrayToVector(jsonData[prop_additionalLibraries.name]);
    languageCompiler = jsonData[prop_languageCompiler.name];
    languageVersion = jsonData[prop_languageVersion.name];
    currentBuildSetting = jsonData[prop_currentBuildSetting.name];
    buildSettings = BuildSetting::vectorFromJson(jsonData[prop_buildSettings.name]);
}


json ProjectData::toJson() const noexcept
{
	return {
		{ prop_name.name, name },
		{ prop_type.name, projectTypeToString(type) },
		{ prop_dependencies.name, dependencies },
		{ prop_sourceDirectory.name, sourceDirectory },
		{ prop_headerDirectory.name, headerDirectory },
		{ prop_buildDirectory.name, buildDirectory },
		{ prop_additionalIncludePaths.name, additionalIncludePaths },
		{ prop_additionalLibraryPaths.name, additionalLibraryPaths },
		{ prop_additionalLibraries.name, additionalLibraries },
		{ prop_languageCompiler.name, languageCompiler },
		{ prop_languageVersion.name, languageVersion },
		{ prop_currentBuildSetting.name, currentBuildSetting },
		{ prop_buildSettings.name, BuildSetting::toJsonArray(buildSettings) }
	};
}





ProjectDataManager::ProjectDataManager(const ProjectData& data) : _data(data)
{}


ProjectDataManager::ProjectDataManager(const json& jsonData) : ProjectDataManager(ProjectData(jsonData))
{}



void ProjectDataManager::print() const noexcept
{
    std::cout << "name: " << _data.name << std::endl;
    std::cout << "type: " << projectTypeToString(_data.type) << std::endl;
    std::cout << "dependencies: " << joinStringVector(_data.dependencies, ", ") << std::endl;

    std::cout << "source directory: " << _data.sourceDirectory << std::endl;
    std::cout << "header directory: " << _data.headerDirectory << std::endl;
    std::cout << "build directory: " << _data.buildDirectory << std::endl;
    std::cout << "additional include paths: " << joinStringVector(_data.additionalIncludePaths, ", ") << std::endl;
    std::cout << "additional library paths: " << joinStringVector(_data.additionalLibraryPaths, ", ") << std::endl;
    std::cout << "additional libraries: " << joinStringVector(_data.additionalLibraries, ", ") << std::endl;

    std::cout << "language compiler: " << _data.languageCompiler << std::endl;
    std::cout << "language version: " << _data.languageVersion << std::endl;

    std::cout << "current build setting: " << _data.currentBuildSetting << std::endl;
    std::cout << "build settings: " << joinStringVector(BuildSetting::getBuildSettingNames(_data.buildSettings), ", ") << std::endl;
}



void ProjectDataManager::writeToFile(const ProjectData& data, const std::string& path)
{
	writeJsonToFile(data.toJson(), path);
}


ProjectDataManager ProjectDataManager::readFromFile(const std::string& path)
{
	return ProjectDataManager(readJsonFromFile(path));
}
