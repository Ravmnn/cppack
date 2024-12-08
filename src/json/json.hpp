#pragma once

#include <nlohmann_json.hpp>


using json = nlohmann::ordered_json;



std::vector<std::string> convertJsonStringArrayToVector(const json& stringArray);


json readJsonFromFile(const std::string& path);
void writeJsonToFile(const json& data, const std::string& path);



std::string jsonTypeToString(json::value_t type) noexcept;



class JsonConversible
{
public:
	virtual void fromJson(const json& jsonData) = 0;
	virtual json toJson() const noexcept = 0;
};



struct JsonPropertyValidationRequirements
{
	std::string name;
	json::value_t type;

	json::value_t arrayItemType = json::value_t::null;
};


class JsonPropertiesValidator
{
protected:
	std::vector<JsonPropertyValidationRequirements> propertiesRequirements;


public:
	virtual void validateProperties(const json& jsonData) const;


protected:
	JsonPropertiesValidator(const std::vector<JsonPropertyValidationRequirements>& propertiesRequirements = {}) noexcept;
};
