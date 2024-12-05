#pragma once

#include <string>
#include <vector>
#include <map>

#include <json.hpp>


using json = nlohmann::json;



enum class BuildOptimizationType
{
    None,
    Low,
    Medium,
    High,
    Extreme,
    Shrink,
    ExtremeShrink,
    Debug
};

std::string buildOptimizationTypeToString(BuildOptimizationType level);
BuildOptimizationType buildOptimizationTypeFromString(std::string source);



enum class BuildWarningType
{
    None,
    Normal,
    All,
    Extra
};

std::string buildWarningTypeToString(BuildWarningType level);
BuildWarningType buildWarningTypeFromString(std::string source);



enum class ProjectType
{
    Executable,
    Library
};

std::string projectTypeToString(ProjectType type);
ProjectType projectTypeFromString(std::string source);



struct BuildSettings
{
    BuildOptimizationType optimizationType;
    BuildWarningType warningType;

    std::vector<std::string> defines;
    
    std::string additionalOptions;
};

BuildSettings buildSettingsFromJson(json jsonData);



struct ProjectData
{
    std::string name;
    ProjectType type;

    std::vector<std::string> dependencies;

    std::string sourceDirectory;
    std::string headerDirectory;
    std::vector<std::string> additionalIncludePaths;

    std::string currentBuildSetting;
    std::map<std::string, BuildSettings> buildSettings;
};


ProjectData projectDataFromJson(json jsonData);


void printProjectData(ProjectData data);