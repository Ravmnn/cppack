#pragma once

#include <string>



class Project;


class GlobalPackageIndex
{
public:
	GlobalPackageIndex() = delete;


	static void registerPackage(const Project& project);
	static void unregisterPackage(const std::string& name);
	static bool isPackageRegistered(const std::string& name) noexcept;

	static Project getPackage(const std::string& name);
};
