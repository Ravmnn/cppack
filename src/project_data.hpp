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


    static BuildSetting fromJson(const json& jsonData) noexcept;
    static std::vector<BuildSetting> vectorFromJson(const json& jsonData) noexcept;

    static std::vector<std::string> getBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept;
};



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


    static ProjectData fromJson(const json& jsonData) noexcept;
};



class ProjectDataManager
{
private:
	ProjectData _projectData;


public:
	ProjectDataManager() = delete;

	ProjectDataManager(const ProjectData& data);
	ProjectDataManager(const json& jsonData);


	void set(const ProjectData& data) noexcept { _projectData = data; }

	const ProjectData& get() const noexcept { return _projectData; }


	void print() const noexcept;
};
