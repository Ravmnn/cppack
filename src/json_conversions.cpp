#include <json_conversions.hpp>

#include <project_data.hpp>



std::vector<std::string> convertJsonStringArrayToVector(const json& array)
{
    std::vector<std::string> stringVector;

    for (auto item : array)
        stringVector.push_back(item);

    return stringVector;
}