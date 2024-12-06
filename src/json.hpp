#pragma once

#include <nlohmann_json.hpp>


using json = nlohmann::json;



std::vector<std::string> convertJsonStringArrayToVector(const json& stringArray);


json readJsonFromFile(const std::string& path);
void writeJsonToFile(const json& data, const std::string& path);



class JsonConversible
{
public:
	virtual void fromJson(const json& jsonData) noexcept = 0;
	virtual json toJson() const noexcept = 0;
};
