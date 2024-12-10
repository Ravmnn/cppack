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


template <typename T>
typename std::vector<T>::const_iterator insertAtEnd(std::vector<T>& vector, const std::vector<T>& other) noexcept
{
	return vector.insert(vector.cend(), other.cbegin(), other.cend());
}
