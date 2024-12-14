#pragma once

#include <utility/file.hpp>
#include <project/project_data.hpp>



class Project
{
private:
	fs::path _projectFilePath;
	bool _hasProjectFilePath;


public:
	static const std::string projectFileExtension;
	static const std::string buildMakefileName;


	explicit Project(const std::string& path);


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
	std::vector<std::string> getLibraries() const noexcept;
	std::vector<std::string> getDependenciesIncludePaths() const noexcept;
	std::vector<std::string> getDependenciesLibraryPaths() const noexcept;
	std::vector<std::string> getDependenciesLibraries() const noexcept;
	std::vector<std::string> getAllIncludePaths() const noexcept;
	std::vector<std::string> getAllLibraryPaths() const noexcept;
	std::vector<std::string> getAllLibraries() const noexcept;


	fs::path toAbsoluteProjectPath(const fs::path& other) const noexcept { return getAbsoluteProjectPath() / other; }

	fs::path getAbsoluteMakefilePath() const noexcept;

	fs::path getAbsoluteBuildPath() const noexcept;
	fs::path getAbsoluteFinalBuildPath() const noexcept;
	fs::path getAbsoluteHeaderPath() const noexcept;
	fs::path getAbsoluteSourcePath() const noexcept;
};
