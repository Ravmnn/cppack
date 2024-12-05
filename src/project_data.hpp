#pragma once

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
BuildOptimizationType buildOptimizationTypeFromString(const std::string& source);




enum class BuildWarningType
{
    None,
    Normal,
    All,
    Extra
};

std::string buildWarningTypeToString(BuildWarningType level);
BuildWarningType buildWarningTypeFromString(const std::string& source);




enum class ProjectType
{
    Executable,
    Library
};

std::string projectTypeToString(ProjectType type);
ProjectType projectTypeFromString(const std::string& source);




struct BuildSetting
{
    std::string name;

    BuildOptimizationType optimizationType;
    BuildWarningType warningType;

    std::vector<std::string> defines;
    
    std::string additionalOptions;
};

BuildSetting buildSettingsFromJson(const json& jsonData);
std::vector<BuildSetting> buildSettingsVectorFromJson(const json& jsonData);

std::vector<std::string> getListOfBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept;




struct ProjectData
{
    std::string name;
    ProjectType type;

    std::vector<std::string> dependencies;

    std::string sourceDirectory;
    std::string headerDirectory;
    std::vector<std::string> additionalIncludePaths;

    std::string currentBuildSetting;
    std::vector<BuildSetting> buildSettings;
};


ProjectData projectDataFromJson(const json& jsonData);




void printProjectData(const ProjectData& data);