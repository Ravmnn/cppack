#include <utility/file.hpp>

#include <filesystem>



void createDirectoryIfNotExists(const std::string& name) noexcept
{
	if (!std::filesystem::exists(name))
		std::filesystem::create_directory(name);
}
