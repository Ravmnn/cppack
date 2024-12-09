#include <commands/command.hpp>

#include <functional>



Command::Command(CPPack* const cppack, CLI::App* const app, const std::string& name, const std::string& description)
	: cppack(cppack), app(app), name(name), description(description)
{
	thisCommand = app->add_subcommand(name, description);
	thisCommand->final_callback([this] () { run(); });
}
