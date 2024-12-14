#pragma once

#include <cppack/exception.hpp>



class CPPack;
class Project;


class InvalidProjectHandlingException : public CPPackException
{
public:
	using CPPackException::CPPackException;


	static void throwIfHasNotProjectFile(const std::string& path);
	static void throwIfHasProjectFile(const std::string& path);

	static void throwIfHasNotProjectFile();
	static void throwIfHasProjectFile();
};



class InvalidPackageIndexHandling : public CPPackException
{
public:
	using CPPackException::CPPackException;


	static void throwIfRegistered(const std::string& name);
	static void throwIfNotRegistered(const std::string& name);

	static void throwIfIsDependency(const Project& project, const std::string& dependencyName);
	static void throwIfIsNotDependency(const Project& project, const std::string& dependencyName);
};
