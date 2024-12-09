#include <make/make_generator.hpp>

#include <utility/file.hpp>
#include <project_data/project_data.hpp>
#include <project_data/project_data_exceptions.hpp>
#include <make/compiler_options.hpp>



MakefileGenerator::MakefileGenerator()
{
	_ignoreNewlines = false;
}



void MakefileGenerator::newline(const unsigned int count) noexcept
{
	if (_ignoreNewlines)
		return;

	for (size_t i = 0; i < count; i++)
		_stream << "\n";
}


void MakefileGenerator::comment(const std::string& message) noexcept
{
	_stream << "# " << message;
	newline();
}


void MakefileGenerator::variable(const std::string& name, const std::string& value) noexcept
{
	_stream << name << " = " << value;
	newline();
}


void MakefileGenerator::variableAdd(const std::string& name, const std::string& value) noexcept
{
	_stream << name << " += " << value;
	newline();
}


void MakefileGenerator::variableWithPrefix(const std::string& name, const std::string& prefix, const std::string& value) noexcept
{
	_stream << name << " = " << prefix << value;
	newline();
}


void MakefileGenerator::listVariableWithPrefix(const std::string& name, const std::string& prefix, const std::vector<std::string>& values) noexcept
{
	_stream << name << " = ";

	for (const std::string& value : values)
		_stream << prefix << value << (&value != &values.back() ? " " : "");

	newline();
}


void MakefileGenerator::rule(const std::string& name, const std::string& dependencies, const bool phony) noexcept
{
	if (phony)
	{
		_stream << ".PHONY:";
		newline();
	}

	_stream << name << ": " << dependencies;
	newline();
}


void MakefileGenerator::patternRule(const std::string& name, const std::string& dep1, const std::string& dep2) noexcept
{
	_stream << name << ": " << dep1 << ": " << dep2;
	newline();
}


void MakefileGenerator::ruleCommand(const std::string& command, bool silent) noexcept
{
	_stream << "\t" << (silent ? "@ " : "") << command;
	newline();
}





static std::string getMakefileCommandForLinkingProjectOfType(const ProjectType type) noexcept
{
	switch (type)
	{
		case ProjectType::Executable: return (std::string)"$(CPP_COMPILER) $(OBJECTS) -o $(BIN_PATH) $(CPP_OPTIONS)";
		case ProjectType::StaticLibrary: return (std::string)"ar rcs $(BIN_PATH) $(OBJECTS)";
		case ProjectType::SharedLibrary: return (std::string)"$(CPP_COMPILER) $(OBJECTS) -o $(BIN_PATH) -shared -fPIC $(CPP_OPTIONS)";

		default: return "invalid";
	}
}


static std::string getMakefileOutFileExtensionForProjectOfType(const ProjectType type) noexcept
{
	switch (type)
	{
		case ProjectType::Executable: return "";
		case ProjectType::StaticLibrary: return ".a";
		case ProjectType::SharedLibrary: return ".so";

		default: return "";
	}
}


void generateMakefileFromProjectData(const std::string& fileToSave, const ProjectData& data)
{
	const BuildSetting* buildSetting = data.buildSetting();

	if (!buildSetting)
		throw InvalidProjectDataException("There are no build settings");


	std::vector<std::string> include_paths = data.additionalIncludePaths;
	include_paths.insert(include_paths.begin(), data.headerDirectory);


	MakefileGenerator make;

	make.comment("This was auto-generated");
	make.newline();

	make.variableAdd("MAKEFLAGS", "-j4");
	make.newline();

	make.variable("NAME", data.name + getMakefileOutFileExtensionForProjectOfType(data.type));
	make.newline();

	make.variable("CURRENT_BUILD_SETTING", data.currentBuildSetting);
	make.newline();

	make.variable("SOURCE_PATH", data.sourceDirectory);
	make.variable("BUILD_PATH", data.buildDirectory);
	make.newline();

	make.variable("COMPLETE_BUILD_PATH", "$(BUILD_PATH)/$(CURRENT_BUILD_SETTING)");
	make.variable("OBJECT_PATH", "$(COMPLETE_BUILD_PATH)/obj");
	make.newline();

	make.variable("BIN_PATH", "$(COMPLETE_BUILD_PATH)/$(NAME)");
	make.newline();

	make.variable("SOURCES", "$(shell find $(SOURCE_PATH) -name \"*.cpp\")");
	make.variable("OBJECTS", "$(addprefix $(OBJECT_PATH)/, $(patsubst $(SOURCE_PATH)/%, %, $(SOURCES:.cpp=.o)))");
	make.newline();

	make.variable("CPP_COMPILER", data.languageCompiler);
	make.variableWithPrefix("CPP_VERSION", "-std=c++", std::to_string(data.languageVersion));
	make.newline();

	make.listVariableWithPrefix("CPP_INCLUDE_PATHS", "-I", include_paths);
	make.variable("CPP_OPTIMIZATION", buildOptimizationTypeToCompilerOption(buildSetting->optimizationType));
	make.variable("CPP_WARNING", buildWarningTypeToCompilerOption(buildSetting->warningType));
	make.listVariableWithPrefix("CPP_DEFINES", "-D", buildSetting->defines);
	make.variable("CPP_ADDITIONAL_OPTIONS", buildSetting->additionalOptions);
	make.newline();

	make.variable("CPP_OPTIONS", "$(CPP_VERSION) $(CPP_INCLUDE_PATHS) $(CPP_OPTIMIZATION) $(CPP_WARNING) $(CPP_DEFINES) $(CPP_ADDITIONAL_OPTIONS)");
	make.newline(2);

	make.rule("build", "$(BIN_PATH)", true);
	make.newline(2);

	make.rule("run", "", true);
		make.ruleCommand("$(BIN_PATH)");
	make.newline(2);

	make.rule("$(BIN_PATH)", "$(OBJECTS)");
		make.ruleCommand(getMakefileCommandForLinkingProjectOfType(data.type));
	make.newline(2);

	make.patternRule("$(OBJECTS)", "$(OBJECT_PATH)/%.o", "$(SOURCE_PATH)/%.cpp");
		make.ruleCommand("mkdir $(dir $@) -p");
		make.ruleCommand("$(CPP_COMPILER) -c $< -o $@ $(CPP_OPTIONS)");


	writeFile(fileToSave, make.get());
}
