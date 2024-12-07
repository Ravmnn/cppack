#pragma once

#include <cppack/exception.hpp>



class ProjectNotFound : public CPPackException
{
public:
	explicit ProjectNotFound(const std::string& message) : CPPackException(message)
	{}
};
