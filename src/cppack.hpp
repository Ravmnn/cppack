#pragma once

#include <string>



class CPPack
{
public:
	CPPack() = delete;
	~CPPack() = delete;


	static const std::string projectFileExtension;


	static std::string projectFilePath;
	static bool hasProjectFilePath;


	static void init(const std::string& path) noexcept;


	static bool directoryContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;
	static bool directoryHierarchyContainsProjectFile(const std::string& path, std::string* projectFilePath = nullptr) noexcept;
};
