#pragma once

#include <project_data.hpp>



class CPPack
{
public:
	CPPack() = delete;
	~CPPack() = delete;


	static const std::string projectFileExtension;


	static std::string projectFilePath;
	static bool hasProjectFilePath;


	static void init(const std::string& path) noexcept;


	static bool directoryContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;
	static bool directoryHierarchyContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;


	static ProjectData generateDefaultProjectData(const std::string& name, ProjectType type) noexcept;
	static BuildSetting generateDefaultBuildSetting(const std::string& name, BuildOptimizationType optimization, BuildWarningType warning) noexcept;


	static void setupProjectEnvironment(const ProjectData& data) noexcept;
};
