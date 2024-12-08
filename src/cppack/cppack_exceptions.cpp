#include <cppack/cppack_exceptions.hpp>

#include <cppack/cppack.hpp>



void InvalidProjectHandlingException::throwIfHasNotProjectFile()
{
	if (!CPPack::hasProjectFilePath)
		throw InvalidProjectHandlingException("Couldn't find a project configuration file");
}


void InvalidProjectHandlingException::throwIfHasProjectFile()
{
	if (CPPack::hasProjectFilePath)
		throw InvalidProjectHandlingException("A project configuration file was found");
}
