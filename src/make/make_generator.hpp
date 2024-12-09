#pragma once

#include <vector>
#include <sstream>



class ProjectData;



class MakefileGenerator
{
private:
	std::stringstream _stream;
	bool _ignoreNewlines;


public:
	MakefileGenerator();


	std::string get() const noexcept { return _stream.str(); }


	void disableNewline() noexcept { _ignoreNewlines = true; }
	void enableNewline() noexcept { _ignoreNewlines = false; }

	void newline(unsigned int count = 1) noexcept;

	void comment(const std::string& message) noexcept;

	void variable(const std::string& name, const std::string& value) noexcept;
	void variableAdd(const std::string& name, const std::string& value) noexcept;
	void variableWithPrefix(const std::string& name, const std::string& prefix, const std::string& value) noexcept;
	void listVariableWithPrefix(const std::string& name, const std::string& prefix, const std::vector<std::string>& values) noexcept;

	void rule(const std::string& name, const std::string& dependencies = "", bool phony = false) noexcept;
	void patternRule(const std::string& name, const std::string& dep1, const std::string& dep2) noexcept;
	void ruleCommand(const std::string& command, bool silent = true) noexcept;
};



void generateMakefileFromProjectData(const std::string& fileToSave, const ProjectData& data);
