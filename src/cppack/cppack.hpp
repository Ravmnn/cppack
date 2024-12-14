#pragma once

#include <utility/file.hpp>
#include <project/project.hpp>
#include <project/project_data.hpp>



class CPPack
{
public:
	static const fs::path cppackDirectoryPath;
	static const fs::path cppackIndexDirectoryPath;


	CPPack() = delete;


	static void init() noexcept;


	static bool directoryContainsProjectFile(const std::string& path, fs::path* projectFilePath = nullptr) noexcept;
	static bool directoryHierarchyContainsProjectFile(const std::string& path, fs::path* projectFilePath = nullptr) noexcept;


	static ProjectData generateDefaultProjectData(const std::string& name, ProjectType type) noexcept;
	static BuildSetting generateDefaultBuildSetting(const std::string& name, BuildOptimizationType optimization, BuildWarningType warning) noexcept;


	static void setupProjectEnvironment(const ProjectData& data) noexcept;
	static void setupCppackGlobalEnvironment() noexcept;
};
