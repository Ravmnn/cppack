#include <utility/vector.hpp>



std::string joinStringVector(const std::vector<std::string>& source, const std::string& separator) noexcept
{
    std::string string;

    for (const std::string& item : source)
        string += item + (item != source.back() ? separator : "");
    
    return string;
}