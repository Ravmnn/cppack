#pragma once

#include <string>



enum class BuildOptimizationType;
enum class BuildWarningType;


std::string buildOptimizationTypeToCompilerOption(BuildOptimizationType optimization) noexcept;
std::string buildWarningTypeToCompilerOption(BuildWarningType warning) noexcept;
