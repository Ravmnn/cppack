#include <utility/file.hpp>

#include <sstream>
#include <fstream>
#include <filesystem>



void createDirectoryIfNotExists(const std::string& name) noexcept
{
	if (!std::filesystem::exists(name))
		std::filesystem::create_directory(name);
}



std::string readFile(const std::string& path)
{
	std::ifstream file(path);
	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
}


void writeFile(const std::string& path, const std::string& content)
{
	std::ofstream file(path);

	file << content;
}
