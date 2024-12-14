#include "package/global_index.hpp"
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





void InvalidPackageIndexHandling::throwIfRegistered(const std::string& name)
{
	if (GlobalPackageIndex::isPackageRegistered(name))
		throw InvalidPackageIndexHandling("Package is registered");
}


void InvalidPackageIndexHandling::throwIfNotRegistered(const std::string& name)
{
	if (!GlobalPackageIndex::isPackageRegistered(name))
		throw InvalidPackageIndexHandling("Package is not registered");
}

void InvalidPackageIndexHandling::throwIfIsDependency(const Project& project, const std::string& dependencyName)
{
	if (project.isPackageADependency(dependencyName))
		throw InvalidPackageIndexHandling("Package is a dependency");
}


void InvalidPackageIndexHandling::throwIfIsNotDependency(const Project& project, const std::string& dependencyName)
{
	if (!project.isPackageADependency(dependencyName))
		throw InvalidPackageIndexHandling("Package is not a dependency");
}
