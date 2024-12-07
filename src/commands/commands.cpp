#include <commands/commands.hpp>

#include <iostream>

#include <cppack.hpp>
#include <project_data.hpp>



CommandInit::CommandInit(CLI::App* const app) : Command(app, "init", "Creates a new project")
{
	thisCommand->add_option("project_type", _projectType)->required();
    thisCommand->add_option("project_name", _projectName);
}


void CommandInit::run() const noexcept
{
	std::cout << "running init command" << std::endl;
}





CommandInfo::CommandInfo(CLI::App* const app) : Command(app, "info", "Prints information about the current project")
{}


void CommandInfo::run() const noexcept
{
	if (!CPPack::hasProjectFilePath)
		return;

	ProjectDataManager(CPPack::projectFilePath).print();
}
