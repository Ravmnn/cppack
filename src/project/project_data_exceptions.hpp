#pragma once

#include <cppack/exception.hpp>



class InvalidProjectDataException : public CPPackException
{
public:
	using CPPackException::CPPackException;
};
