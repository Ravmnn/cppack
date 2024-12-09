#pragma once

#include <project_data/project_data.hpp>



class CPPack
{
public:
	CPPack() = delete;
	~CPPack() = delete;


	static const std::string projectFileExtension;
	static const std::string buildMakefileName;


	static std::string projectFilePath;
	static bool hasProjectFilePath;


	static void init(const std::string& path) noexcept;


	static bool directoryContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;
	static bool directoryHierarchyContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;


	static ProjectData generateDefaultProjectData(const std::string& name, ProjectType type) noexcept;
	static BuildSetting generateDefaultBuildSetting(const std::string& name, BuildOptimizationType optimization, BuildWarningType warning) noexcept;

	static ProjectData getProjectDataFromCurrentProject();


	static const std::string makefileRunRuleName;
	static const std::string makefileBuildRuleName;


	static void generateMakefileFromProjectData(const std::string& fileToSave, const ProjectData& data);

	static std::string getBuildMakefilePath(const ProjectData& data) noexcept;

	static void setupProjectEnvironment(const ProjectData& data) noexcept;
	static void buildProject(const ProjectData& data);
	static void runProject(const ProjectData& data);
	static void cleanProject(const ProjectData& data);
	static void runProjectMakefile(const ProjectData& data, const std::string& makeRule = "");
};
