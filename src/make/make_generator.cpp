#include <make/make_generator.hpp>



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
