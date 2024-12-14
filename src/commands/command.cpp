#include <commands/command.hpp>

#include <functional>



Command::Command(Project* const project, CLI::App* const app, const std::string& name, const std::string& description)
	: project(project), app(app), name(name), description(description)
{
	thisCommand = app->add_subcommand(name, description);
	thisCommand->final_callback([this] () { run(); });
}
