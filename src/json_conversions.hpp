#pragma once

#include <json.hpp>


using json = nlohmann::json;



struct BuildSetting;


std::vector<std::string> convertJsonStringArrayToVector(const json& stringArray);