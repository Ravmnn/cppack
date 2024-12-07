#include <project_data.hpp>

#include <iostream>

#include <utility/vector.hpp>
#include <json.hpp>



std::string buildOptimizationTypeToString(const BuildOptimizationType type)
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


BuildOptimizationType buildOptimizationTypeFromString(const std::string& source)
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





std::string buildWarningTypeToString(const BuildWarningType type)
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


BuildWarningType buildWarningTypeFromString(const std::string& source)
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





std::string projectTypeToString(const ProjectType type)
{
    switch (type)
    {
        case ProjectType::Executable: return "executable";
        case ProjectType::Library:    return "library";

        default: return "invalid";
    }
}


ProjectType projectTypeFromString(const std::string& source)
{
    if (source == "executable") return ProjectType::Executable;
    if (source == "library")    return ProjectType::Library;

    return ProjectType::Executable;
}


bool isProjectTypeStringValid(const std::string& source) noexcept
{
	return projectTypeFromString(source) != ProjectType::Invalid;
}





BuildSetting::BuildSetting(const json& jsonData) noexcept
{
	fromJson(jsonData);
}



void BuildSetting::fromJson(const json& jsonData) noexcept
{
    name = jsonData["name"];
    optimizationType = buildOptimizationTypeFromString(jsonData["optimization"]);
    warningType = buildWarningTypeFromString(jsonData["warning"]);
    defines = convertJsonStringArrayToVector(jsonData["defines"]);
    additionalOptions = jsonData["additional_options"];
}


json BuildSetting::toJson() const noexcept
{
	return {
		{ "name", name },
		{ "optimization", buildOptimizationTypeToString(optimizationType) },
		{ "warning", buildWarningTypeToString(warningType) },
		{ "defines", defines },
		{ "additional_options", additionalOptions }
	};
}



json BuildSetting::toJsonArray(const std::vector<BuildSetting>& data) noexcept
{
	json jsonData;

	for (const BuildSetting& setting : data)
		jsonData[setting.name] = setting.toJson();

	return jsonData;
}


std::vector<BuildSetting> BuildSetting::vectorFromJson(const json& jsonData) noexcept
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





ProjectData::ProjectData(const json& jsonData) noexcept
{
	fromJson(jsonData);
}



void ProjectData::fromJson(const json& jsonData) noexcept
{
    // TODO: add default values if value is null

    name = jsonData["name"];
    type = projectTypeFromString(jsonData["type"]);
    dependencies = convertJsonStringArrayToVector(jsonData["dependencies"]);
    sourceDirectory = jsonData["source_directory"];
    headerDirectory = jsonData["header_directory"];
    additionalIncludePaths = convertJsonStringArrayToVector(jsonData["additional_include_paths"]);
    currentBuildSetting = jsonData["current_build_setting"];
    buildSettings = BuildSetting::vectorFromJson(jsonData["build_settings"]);
}


json ProjectData::toJson() const noexcept
{
	return {
		{ "name", name },
		{ "type", projectTypeToString(type) },
		{ "dependencies", dependencies },
		{ "source_directory", sourceDirectory },
		{ "header_directory", headerDirectory },
		{ "additional_include_paths", additionalIncludePaths },
		{ "current_build_setting", currentBuildSetting },
		{ "build_settings", BuildSetting::toJsonArray(buildSettings) }
	};
}





ProjectDataManager::ProjectDataManager(const ProjectData& data) : _data(data)
{}


ProjectDataManager::ProjectDataManager(const json& jsonData) : ProjectDataManager(ProjectData(jsonData))
{}


ProjectDataManager::ProjectDataManager(const std::string& path) : ProjectDataManager(readJsonFromFile(path))
{}



void ProjectDataManager::print() const noexcept
{
    std::cout << "name: " << _data.name << std::endl;
    std::cout << "type: " << projectTypeToString(_data.type) << std::endl;
    std::cout << "dependencies: " << joinStringVector(_data.dependencies, ", ") << std::endl;

    std::cout << "source directory: " << _data.sourceDirectory << std::endl;
    std::cout << "header directory: " << _data.headerDirectory << std::endl;
    std::cout << "additional include paths: " << joinStringVector(_data.additionalIncludePaths, ", ") << std::endl;

    std::cout << "current build setting: " << _data.currentBuildSetting << std::endl;
    std::cout << "build settings: " << joinStringVector(BuildSetting::getBuildSettingNames(_data.buildSettings), ", ") << std::endl;
}



void ProjectDataManager::writeToFile(const std::string& path) const
{
	writeJsonToFile(_data.toJson(), path);
}


void ProjectDataManager::readFromFile(const std::string& path)
{
	_data.fromJson(readJsonFromFile(path));
}
