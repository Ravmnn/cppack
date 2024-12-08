#pragma once

#include <string>



void createDirectoryIfNotExists(const std::string& name) noexcept;


std::string readFile(const std::string& path);
void writeFile(const std::string& path, const std::string& content);
