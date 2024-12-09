#pragma once

#include <utility/file.hpp>
#include <project_data/project_data.hpp>



class CPPack
{
private:
	fs::path _projectFilePath;
	bool _hasProjectFilePath;


public:
	static const fs::path cppackDirectoryPath;
	static const fs::path cppackIndexDirectoryPath;

	static const std::string projectFileExtension;
	static const std::string buildMakefileName;


	explicit CPPack(const std::string& path);


	fs::path getAbsoluteProjectFilePath() const noexcept { return fs::absolute(_projectFilePath); }
	fs::path getAbsoluteProjectPath() const noexcept { return fs::absolute(_projectFilePath.parent_path()); }
	bool hasProjectFilePath() const noexcept { return _hasProjectFilePath; }

	ProjectData getData() const { return ProjectDataManager::readFromFile(getAbsoluteProjectFilePath()).getData(); }


	std::string getProjectOutFileExtension() const noexcept;
	std::string getProjectOutFileStem() const noexcept;
	std::string getProjectFullOutFileName() const noexcept;


	void buildProject() const;
	void buildProjectDependencies() const;
	void runProject() const;
	void cleanProject() const;
	void runProjectMakefile(const std::string& makeRule) const;


	void addPackageDependency(const std::string& name) const;
	void removePackageDependency(const std::string& name) const;
	bool isPackageADependency(const std::string& name) const noexcept;


	std::vector<std::string> getIncludePaths(bool includeProject = true) const noexcept;
	std::vector<std::string> getLibraryPaths(bool includeProject = true) const noexcept;
	std::vector<std::string> getDependenciesIncludePaths() const noexcept;
	std::vector<std::string> getDependenciesLibraryPaths() const noexcept;
	std::vector<std::string> getAllIncludePaths() const noexcept;
	std::vector<std::string> getAllLibraryPaths() const noexcept;


	fs::path toAbsoluteProjectPath(const fs::path& other) const noexcept { return getAbsoluteProjectPath() / other; }

	fs::path getAbsoluteMakefilePath() const noexcept;

	fs::path getAbsoluteBuildPath() const noexcept;
	fs::path getAbsoluteFinalBuildPath() const noexcept;
	fs::path getAbsoluteHeaderPath() const noexcept;
	fs::path getAbsoluteSourcePath() const noexcept;


	static void init() noexcept;


	static void registerPackage(const CPPack& project);
	static void unregisterPackage(const std::string& name);
	static bool isPackageRegistered(const std::string& name) noexcept;

	static CPPack getPackage(const std::string& name);


	static bool directoryContainsProjectFile(const std::string& path, fs::path* projectFilePath = nullptr) noexcept;
	static bool directoryHierarchyContainsProjectFile(const std::string& path, fs::path* projectFilePath = nullptr) noexcept;


	static ProjectData generateDefaultProjectData(const std::string& name, ProjectType type) noexcept;
	static BuildSetting generateDefaultBuildSetting(const std::string& name, BuildOptimizationType optimization, BuildWarningType warning) noexcept;


	static void setupProjectEnvironment(const ProjectData& data) noexcept;
	static void setupCppackGlobalEnvironment() noexcept;
};
