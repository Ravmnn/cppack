#pragma once

#include <cppack/exception.hpp>



class InvalidProjectHandlingException : public CPPackException
{
public:
	using CPPackException::CPPackException;


	static void throwIfHasNotProjectFile();
	static void throwIfHasProjectFile();
};
