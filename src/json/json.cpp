#include <json/json.hpp>

#include <fstream>

#include <json/json_exceptions.hpp>



std::vector<std::string> convertJsonStringArrayToVector(const json& array)
{
    std::vector<std::string> stringVector;

    for (auto item : array)
        stringVector.push_back(item);

    return stringVector;
}



json readJsonFromFile(const std::string& path)
{
	return json::parse(std::ifstream(path));
}



void writeJsonToFile(const json& data, const std::string& path)
{
	std::ofstream file(path);

	file << data.dump(2);
}





std::string jsonTypeToString(const json::value_t type) noexcept
{
	switch (type)
	{
		case json::value_t::string: return "string";
		case json::value_t::number_float: return "float";
		case json::value_t::number_integer: return "integer";
		case json::value_t::number_unsigned: return "unsigned_integer";
		case json::value_t::boolean: return "boolean";
		case json::value_t::array: return "array";
		case json::value_t::object: return "object";
		case json::value_t::null: return "null";
		case json::value_t::discarded: return "discarded";

		default: return "invalid";
	}
}





JsonPropertiesValidator::JsonPropertiesValidator(const std::vector<JsonPropertyValidationRequirements>& propertiesRequirements) noexcept
	: propertiesRequirements(propertiesRequirements)
{}



void JsonPropertiesValidator::validateProperties(const json& jsonData) const
{
	for (const JsonPropertyValidationRequirements& propertyRequirement : propertiesRequirements)
	{
		const std::string& name = propertyRequirement.name;
		const json::value_t& type = propertyRequirement.type;
		const json::value_t& arrayItemType = propertyRequirement.arrayItemType;

		InvalidJsonObjectFormat::throwIfJsonKeyDoesNotExist(jsonData, name);
		InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(jsonData, name, type);

		if (type != json::value_t::array || arrayItemType == json::value_t::null)
			continue;

		InvalidJsonObjectFormat::throwIfJsonValueIsNotAnArrayOfType(jsonData, name, arrayItemType);
	}
}
