#pragma once

#include <json/json.hpp>



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

std::string buildOptimizationTypeToString(BuildOptimizationType level) noexcept;
BuildOptimizationType buildOptimizationTypeFromString(const std::string& source) noexcept;

bool isBuildOptimizationStringValid(const std::string& source) noexcept;




enum class BuildWarningType
{
	Invalid,

    None,
    Normal,
    All,
    Extra
};

std::string buildWarningTypeToString(BuildWarningType level) noexcept;
BuildWarningType buildWarningTypeFromString(const std::string& source) noexcept;

bool isBuildWarningTypeStringValid(const std::string& source) noexcept;




enum class ProjectType
{
	Invalid,

    Executable,
    Library
};

std::string projectTypeToString(ProjectType type) noexcept;
ProjectType projectTypeFromString(const std::string& source) noexcept;

bool isProjectTypeStringValid(const std::string& source) noexcept;




class BuildSetting : public JsonConversible, private JsonPropertiesValidator
{
public:
	static const JsonPropertyValidationRequirements prop_name;
	static const JsonPropertyValidationRequirements prop_optimizationType;
	static const JsonPropertyValidationRequirements prop_warningType;
	static const JsonPropertyValidationRequirements prop_defines;
	static const JsonPropertyValidationRequirements prop_additionalOptions;


    std::string name;

    BuildOptimizationType optimizationType;
    BuildWarningType warningType;

    std::vector<std::string> defines;

    std::string additionalOptions;


    explicit BuildSetting(const json& jsonData);
    BuildSetting();


    void fromJson(const json& jsonData) override;
    json toJson() const noexcept override;


    static json toJsonArray(const std::vector<BuildSetting>& data) noexcept;
    static std::vector<BuildSetting> vectorFromJson(const json& jsonData);

    static std::vector<std::string> getBuildSettingNames(const std::vector<BuildSetting>& settings) noexcept;
};



class ProjectData : public JsonConversible, private JsonPropertiesValidator
{
public:
	static const JsonPropertyValidationRequirements prop_name;
	static const JsonPropertyValidationRequirements prop_type;
	static const JsonPropertyValidationRequirements prop_dependencies;
	static const JsonPropertyValidationRequirements prop_sourceDirectory;
	static const JsonPropertyValidationRequirements prop_headerDirectory;
	static const JsonPropertyValidationRequirements prop_buildDirectory;
	static const JsonPropertyValidationRequirements prop_additionalIncludePaths;
	static const JsonPropertyValidationRequirements prop_languageCompiler;
	static const JsonPropertyValidationRequirements prop_languageVersion;
	static const JsonPropertyValidationRequirements prop_currentBuildSetting;
	static const JsonPropertyValidationRequirements prop_buildSettings;


    std::string name;
    ProjectType type;

    std::vector<std::string> dependencies;

    std::string sourceDirectory;
    std::string headerDirectory;
    std::string buildDirectory;
    std::vector<std::string> additionalIncludePaths;

    std::string languageCompiler;
    unsigned int languageVersion;

    std::string currentBuildSetting;
    std::vector<BuildSetting> buildSettings;

    explicit ProjectData(const json& jsonData);
    ProjectData();


    void fromJson(const json& jsonData) override;
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
	explicit ProjectDataManager(const std::string& path);


	const ProjectData& get_data() const noexcept { return _data; }

	void set_data(const ProjectData& data) noexcept { _data = data; }


	void print() const noexcept;


	void writeToFile(const std::string& path) const;
	void readFromFile(const std::string& path);
};
