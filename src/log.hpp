#pragma once

#include <iostream>



template <typename... T>
void print(const T&... values)
{
	(std::cout << ... << values);
}


template <typename... T>
void printl(const T&... values)
{
	(std::cout << ... << values) << std::endl;
}
