#include <json/json_exceptions.hpp>

#include <json/json.hpp>
#include <cppack/exception.hpp>



InvalidJsonObjectFormat::InvalidJsonObjectFormat(const std::string& message) : CPPackException(message)
{}



void InvalidJsonObjectFormat::throwIfJsonKeyDoesNotExist(const json& jsonData, const std::string& key)
{
	if (!jsonData.contains(key))
		throw InvalidJsonObjectFormat("JSON key \"" + key + "\" does not exist");
}


void InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(const json& jsonData, const std::string& property, json::value_t type)
{
	if (jsonData[property].type() != type)
		throw InvalidJsonObjectFormat("JSON property \"" + property + "\" must be of type \"" + jsonTypeToString(type) + "\"");
}


void InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(const json& jsonData, const size_t index, const json::value_t type, const std::string& parentKey)
{
	if (jsonData[index].type() != type)
		throw InvalidJsonObjectFormat("JSON array value at index " + std::to_string(index) + " must be of type \"" + jsonTypeToString(type) + "\""
			+ (parentKey.empty() ? "" : " (\"" + parentKey + "\")"));
}



void InvalidJsonObjectFormat::throwIfJsonValueIsNotAnArrayOfType(const json &jsonData, const std::string &property, json::value_t type)
{
	throwIfJsonValueIsNotOfType(jsonData, property, json::value_t::array);

	for (size_t i = 0; i < jsonData[property].size(); i++)
		InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(jsonData[property], i, type, property);
}
