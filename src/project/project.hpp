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
	static const std::string makefileName;


	explicit Project(const std::string& path);


	fs::path getAbsoluteProjectFilePath() const noexcept { return fs::absolute(_projectFilePath); }
	fs::path getAbsoluteProjectPath() const noexcept { return fs::absolute(_projectFilePath.parent_path()); }
	bool hasProjectFilePath() const noexcept { return _hasProjectFilePath; }

	ProjectData getData() const { return ProjectDataManager::readFromFile(getAbsoluteProjectFilePath()).getData(); }
	void setData(const ProjectData& data) const { ProjectDataManager::writeToFile(data, getAbsoluteProjectFilePath()); }



	std::string getProjectOutFileExtension() const noexcept;
	std::string getProjectOutFileStem() const noexcept;
	std::string getProjectFullOutFileName() const noexcept;


	void buildProject() const;
	void runProject() const;
	void cleanProject() const;
	void runProjectMakefile(const std::string& makeRule) const;

	void makefyProject() const;


private:
	std::vector<std::string> getPaths(const std::string& main, const std::vector<std::string>& additional, bool includeProject = true, bool absolutePaths = true) const noexcept;

public:
	std::vector<std::string> getIncludePaths(bool includeProject = true, bool absolutePaths = true) const noexcept;
	std::vector<std::string> getLibraryPaths(bool includeProject = true, bool absolutePaths = true) const noexcept;
	std::vector<std::string> getLibraries() const noexcept;


	fs::path toAbsoluteProjectPath(const fs::path& other) const noexcept { return getAbsoluteProjectPath() / other; }

	fs::path getMakefilePath(bool absolutePath = true) const noexcept;
	fs::path getIndependentMakefilePath(bool absolutePath = true) const noexcept;

	fs::path getBuildPath(bool absolutePath = true) const noexcept;
	fs::path getFinalBuildPath(bool absolutePath = true) const noexcept;
	fs::path getHeaderPath(bool absolutePath = true) const noexcept;
	fs::path getSourcePath(bool absolutePath = true) const noexcept;
};
