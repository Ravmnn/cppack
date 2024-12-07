#include "nlohmann_json.hpp"
#include <json/json.hpp>
#include <json/json_exceptions.hpp>

#include <cppack/exception.hpp>



InvalidJsonObjectFormat::InvalidJsonObjectFormat(const std::string& message) : CPPackException(message)
{}



void InvalidJsonObjectFormat::throwIfJsonKeyDoesNotExist(const json& jsonData, const std::string& property)
{
	if (!jsonData.contains(property))
		throw InvalidJsonObjectFormat("JSON property \"" + property + "\" is missing");
}


void InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(const json& jsonData, const std::string& property, const json::value_t type)
{
	if (jsonData[property].type() != type)
		throw InvalidJsonObjectFormat("JSON property \"" + property + "\" must be of type " + nlohmann::to_string(nlohmann::basic_json<>(type)));
}
