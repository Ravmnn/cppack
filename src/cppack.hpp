#pragma once

#include <string>



class CPPack
{
public:
	CPPack() = delete;
	~CPPack() = delete;


	static const std::string project_file_extension;


	static bool currentDirectoryContainsProjectFile() noexcept;
};
