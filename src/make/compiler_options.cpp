#include <make/compiler_options.hpp>

#include <project_data/project_data.hpp>



std::string buildOptimizationTypeToCompilerOption(BuildOptimizationType optimization) noexcept
{
	switch (optimization)
	{
		case BuildOptimizationType::None: return "-O0";
		case BuildOptimizationType::Low: return "-O1";
		case BuildOptimizationType::Medium: return "-O2";
		case BuildOptimizationType::High: return "-O3";
		case BuildOptimizationType::Extreme: return "-Ofast";
		case BuildOptimizationType::Shrink: return "-Os";
		case BuildOptimizationType::ExtremeShrink: return "-Oz";
		case BuildOptimizationType::Debug: return "-Og";

		default: return "";
	}
}


std::string buildWarningTypeToCompilerOption(BuildWarningType warning) noexcept
{
	switch (warning)
	{
		case BuildWarningType::None: return "-w";
		case BuildWarningType::Normal: return "";
		case BuildWarningType::All: return "-Wall";
		case BuildWarningType::Extra: return "-Wall -Wextra";

		default: return "";
	}
}
