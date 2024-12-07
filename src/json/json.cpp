#include <json/json.hpp>

#include <fstream>

#include <project_data.hpp>
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

	file << data.dump(4);
}





JsonPropertiesValidator::JsonPropertiesValidator(const std::vector<JsonPropertyValidationRequirements>& propertiesRequirements) noexcept
	: propertiesRequirements(propertiesRequirements)
{}



void JsonPropertiesValidator::validateProperties(const json& jsonData) const
{
	for (const JsonPropertyValidationRequirements& propertyRequirement : propertiesRequirements)
	{
		InvalidJsonObjectFormat::throwIfJsonKeyDoesNotExist(jsonData, propertyRequirement.name);
		InvalidJsonObjectFormat::throwIfJsonValueIsNotOfType(jsonData, propertyRequirement.name, propertyRequirement.type);
	}
}
