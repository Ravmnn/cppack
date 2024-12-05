#include <project_data.hpp>

#include <iostream>

#include <json_conversions.hpp>
#include <utility/vector.hpp>



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





std::string projectTypeToString(const ProjectType type)
{
    switch (type)
    {
        case ProjectType::Executable: return "executable";
        case ProjectType::Library: return "library";

        default: return "invalid";
    }
}


ProjectType projectTypeFromString(const std::string& source)
{
    if (source == "executable") return ProjectType::Executable;
    if (source == "library") return ProjectType::Library;

    return ProjectType::Executable;
}





BuildSetting buildSettingsFromJson(const json& jsonData)
{
    // TODO: code like that can use the "Type { .member = val }" syntax

    BuildSetting settings;

    settings.name = jsonData["name"];
    settings.optimizationType = buildOptimizationTypeFromString(jsonData["optimization"]);
    settings.warningType = buildWarningTypeFromString(jsonData["warning"]);
    settings.defines = convertJsonStringArrayToVector(jsonData["defines"]);
    settings.additionalOptions = jsonData["additional_options"];

    return settings;
}


std::vector<BuildSetting> buildSettingsVectorFromJson(const json& jsonData)
{
    std::vector<BuildSetting> buildSettings;

    for (const auto& item : jsonData)
        buildSettings.push_back(buildSettingsFromJson(item));

    return buildSettings;
}


std::vector<std::string> getListOfBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept
{
    std::vector<std::string> names;

    for (const BuildSetting& setting : settings)
        names.push_back(setting.name);

    return names;
}





ProjectData projectDataFromJson(const json& jsonData)
{
    ProjectData data;

    // TODO: add default values if value is null

    data.name = jsonData["project_name"];
    data.type = projectTypeFromString(jsonData["project_type"]);
    data.dependencies = convertJsonStringArrayToVector(jsonData["project_dependencies"]);
    data.sourceDirectory = jsonData["project_source_directory"];
    data.headerDirectory = jsonData["project_header_directory"];
    data.additionalIncludePaths = convertJsonStringArrayToVector(jsonData["additional_include_paths"]);
    data.currentBuildSetting = jsonData["current_build_setting"];
    data.buildSettings = buildSettingsVectorFromJson(jsonData["build_settings"]);

    return data;
}





static void printStringVector(const std::vector<std::string>& vector)
{
    for (const std::string& item : vector)
        std::cout << item << (item != vector.back() ? ", " : "");
}


void printProjectData(const ProjectData& data)
{
    std::cout << "name: " << data.name << std::endl;
    std::cout << "type: " << projectTypeToString(data.type) << std::endl;
    std::cout << "dependencies: " << joinStringVector(data.dependencies, ", ") << std::endl;

    std::cout << "source directory: " << data.sourceDirectory << std::endl;
    std::cout << "header directory: " << data.headerDirectory << std::endl;
    std::cout << "additional include paths: " << joinStringVector(data.additionalIncludePaths, ", ") << std::endl;

    std::cout << "current build setting: " << data.currentBuildSetting << std::endl;
    std::cout << "build settings: " << joinStringVector(getListOfBuildSettingNames(data.buildSettings), ", ") << std::endl;
}