#pragma once

#include <json.hpp>


using json = nlohmann::json;



enum class BuildOptimizationType
{
	Invalid,

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

bool isBuildOptimizationStringValid(const std::string& source) noexcept;




enum class BuildWarningType
{
	Invalid,

    None,
    Normal,
    All,
    Extra
};

std::string buildWarningTypeToString(BuildWarningType level);
BuildWarningType buildWarningTypeFromString(const std::string& source);

bool isBuildWarningTypeStringValid(const std::string& source) noexcept;




enum class ProjectType
{
	Invalid,

    Executable,
    Library
};

std::string projectTypeToString(ProjectType type);
ProjectType projectTypeFromString(const std::string& source);

bool isProjectTypeStringValid(const std::string& source) noexcept;




class BuildSetting : public JsonConversible
{
public:
    std::string name;

    BuildOptimizationType optimizationType;
    BuildWarningType warningType;

    std::vector<std::string> defines;

    std::string additionalOptions;


    explicit BuildSetting(const json& jsonData) noexcept;


    void fromJson(const json& jsonData) noexcept override;
    json toJson() const noexcept override;


    static json toJsonArray(const std::vector<BuildSetting>& data) noexcept;
    static std::vector<BuildSetting> vectorFromJson(const json& jsonData) noexcept;

    static std::vector<std::string> getBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept;
};



class ProjectData : public JsonConversible
{
public:
    std::string name;
    ProjectType type;

    std::vector<std::string> dependencies;

    std::string sourceDirectory;
    std::string headerDirectory;
    std::vector<std::string> additionalIncludePaths;

    std::string currentBuildSetting;
    std::vector<BuildSetting> buildSettings;


    explicit ProjectData(const json& jsonData) noexcept;


    void fromJson(const json& jsonData) noexcept override;
    json toJson() const noexcept override;
};



class ProjectDataManager
{
private:
	ProjectData _data;


public:
	ProjectDataManager() = delete;

	explicit ProjectDataManager(const ProjectData& data);
	explicit ProjectDataManager(const json& jsonData);


	const ProjectData& get_data() const noexcept { return _data; }

	void set_data(const ProjectData& data) noexcept { _data = data; }


	void print() const noexcept;


	void writeToFile(const std::string& path) const;
	void readFromFile(const std::string& path);
};
