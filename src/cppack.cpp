#include <cppack.hpp>

#include <filesystem>


namespace stdfs = std::filesystem;



const std::string CPPack::project_file_extension = ".cpproj";



bool CPPack::currentDirectoryContainsProjectFile() noexcept
{
	for (const auto& file : stdfs::directory_iterator(stdfs::current_path()))
		if (file.path().extension() == project_file_extension)
			return true;

	return false;
}
