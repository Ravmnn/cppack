#pragma once

#include <filesystem>


namespace fs = std::filesystem;



void createDirectoryIfNotExists(const std::string& name) noexcept;


std::string readFile(const std::string& path);
void writeFile(const std::string& path, const std::string& content);


fs::path getHomeDirectoryPath() noexcept;
