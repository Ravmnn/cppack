#pragma once

#include <nlohmann_json.hpp>


using json = nlohmann::json;



std::vector<std::string> convertJsonStringArrayToVector(const json& stringArray);


json readJsonFromFile(const std::string& path);
void writeJsonToFile(const json& data, const std::string& path);



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
};


class JsonPropertiesValidator
{
protected:
	std::vector<JsonPropertyValidationRequirements> propertiesRequirements;


public:
	JsonPropertiesValidator() = delete;


	virtual void validateProperties(const json& jsonData) const;


protected:
	explicit JsonPropertiesValidator(const std::vector<JsonPropertyValidationRequirements>& propertiesRequirements) noexcept;
};
