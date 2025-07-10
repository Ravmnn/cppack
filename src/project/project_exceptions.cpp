#include <project/project_exceptions.hpp>

#include <cppack/cppack.hpp>



void InvalidProjectHandlingException::throwIfHasNotProjectFile(const std::string& path)
{
	if (!CPPack::directoryHierarchyContainsProjectFile(path))
		throw InvalidProjectHandlingException("Couldn't find a project configuration file");
}


void InvalidProjectHandlingException::throwIfHasProjectFile(const std::string& path)
{
	if (CPPack::directoryHierarchyContainsProjectFile(path))
		throw InvalidProjectHandlingException("A project configuration file was found");
}


void InvalidProjectHandlingException::throwIfHasNotProjectFile()
{
	throwIfHasNotProjectFile(fs::current_path());
}


void InvalidProjectHandlingException::throwIfHasProjectFile()
{
	throwIfHasProjectFile(fs::current_path());
}
