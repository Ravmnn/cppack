#include <cppack/cppack.hpp>

#include <filesystem>



const std::string CPPack::projectFileExtension = ".cpproj";


std::string CPPack::projectFilePath = "";
bool CPPack::hasProjectFilePath = false;



void CPPack::init(const std::string& path) noexcept
{
	hasProjectFilePath = directoryHierarchyContainsProjectFile(path, &projectFilePath);
}



bool CPPack::directoryContainsProjectFile(const std::string& path, std::string* const projectFilePath) noexcept
{
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().extension() != projectFileExtension)
			continue;

		if (projectFilePath)
			*projectFilePath = file.path();

		return true;
	}

	return false;
}


bool CPPack::directoryHierarchyContainsProjectFile(const std::string& path, std::string* const projectFilePath) noexcept
{
	const std::filesystem::path ppath = path;

	if (directoryContainsProjectFile(ppath, projectFilePath))
		return true;

	return ppath != ppath.root_path() ? directoryHierarchyContainsProjectFile(ppath.parent_path(), projectFilePath) : false;
}
