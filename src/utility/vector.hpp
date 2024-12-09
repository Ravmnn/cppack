#pragma once

#include <string>
#include <vector>
#include <algorithm>



std::string joinStringVector(const std::vector<std::string>& source, const std::string& separator = " ") noexcept;


template <typename T>
typename std::vector<T>::const_iterator find(const std::vector<T>& vector, const T& value) noexcept
{
	return std::find(vector.cbegin(), vector.cend(), value);
}
