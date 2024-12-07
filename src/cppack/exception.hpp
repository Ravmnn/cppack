#pragma once

#include <string>
#include <exception>



class CPPackException : public std::exception
{
public:
	const std::string message;


	explicit CPPackException(const std::string& message) noexcept;


	const char* what() const noexcept override;
};
