#include <project_data.hpp>

#include <iostream>
#include <stdexcept>



std::string buildOptimizationTypeToString(BuildOptimizationType type)
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


BuildOptimizationType buildOptimizationTypeFromString(std::string source)
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





std::string buildWarningTypeToString(BuildWarningType type)
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


BuildWarningType buildWarningTypeFromString(std::string source)
{
    if (source == "none")   return BuildWarningType::None;
    if (source == "normal") return BuildWarningType::Normal;
    if (source == "all")    return BuildWarningType::All;
    if (source == "extra")  return BuildWarningType::Extra;

    return BuildWarningType::None;
}





std::string projectTypeToString(ProjectType type)
{
    switch (type)
    {
        case ProjectType::Executable: return "executable";
        case ProjectType::Library: return "library";

        default: return "invalid";
    }
}


ProjectType projectTypeFromString(std::string source)
{
    if (source == "executable") return ProjectType::Executable;
    if (source == "library") return ProjectType::Library;

    return ProjectType::Executable;
}




// TODO: move this to "json_conversions.cpp"
static std::vector<std::string> jsonStringArrayToStringVector(json array)
{
    std::vector<std::string> stringVector;

    for (auto item : array)
        stringVector.push_back(item);

    return stringVector;
}



BuildSettings buildSettingsFromJson(json jsonData)
{
    // TODO: code like that can use the "Type { .member = val }" syntax

    BuildSettings settings;

    settings.optimizationType = buildOptimizationTypeFromString(jsonData["optimization"]);
    settings.warningType = buildWarningTypeFromString(jsonData["warning"]);
    settings.defines = jsonStringArrayToStringVector(jsonData["defines"]);
    settings.additionalOptions = jsonData["additional_options"];

    return settings;
}



static std::map<std::string, BuildSettings> jsonBuildModesToMap(json jsonData)
{
    std::map<std::string, BuildSettings> buildSettings;

    for (auto buildModeName : jsonData.items())
        buildSettings[buildModeName.key()] = buildSettingsFromJson(jsonData[buildModeName.key()]);

    return buildSettings;
}



ProjectData projectDataFromJson(json jsonData)
{
    ProjectData data;

    // TODO: add default values if value is null

    data.name = jsonData["project_name"];
    data.type = projectTypeFromString(jsonData["project_type"]);
    data.dependencies = jsonStringArrayToStringVector(jsonData["project_dependencies"]);
    data.sourceDirectory = jsonData["project_source_directory"];
    data.headerDirectory = jsonData["project_header_directory"];
    data.additionalIncludePaths = jsonStringArrayToStringVector(jsonData["additional_include_paths"]);
    data.currentBuildSetting = jsonData["current_build_setting"];
    data.buildSettings = jsonBuildModesToMap(jsonData["build_settings"]);

    return data;
}





void printProjectData(ProjectData data)
{
    // TODO: print string arrays

    std::cout << "name: " << data.name << std::endl;
    std::cout << "type: " << projectTypeToString(data.type) << std::endl;
    std::cout << "dependencies: " << data.dependencies.size() << std::endl;
    std::cout << "source directory: " << data.sourceDirectory << std::endl;
    std::cout << "header directory: " << data.headerDirectory << std::endl;
    std::cout << "additional include paths: " << data.additionalIncludePaths.size() << std::endl;
    std::cout << "current build setting: " << data.currentBuildSetting << std::endl;
    std::cout << "build settings: " << data.buildSettings.size() << std::endl;
}