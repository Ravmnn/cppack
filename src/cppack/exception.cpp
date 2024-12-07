#include <cppack/exception.hpp>



CPPackException::CPPackException(const std::string& message) noexcept : message(message)
{}



const char* CPPackException::what() const noexcept
{
	return message.c_str();
}
