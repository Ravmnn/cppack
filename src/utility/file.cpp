#include <utility/file.hpp>

#include <fstream>



void createDirectoryIfNotExists(const std::string& name) noexcept
{
	if (!fs::exists(name))
		fs::create_directories(name);
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




fs::path getHomeDirectoryPath() noexcept
{
	return getenv("HOME");
}
