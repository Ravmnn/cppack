#include <commands/commands.hpp>

#include <cppack/cppack.hpp>



CommandInit::CommandInit(CLI::App* const app) : Command(app, "init", "Creates a new project")
{
	thisCommand->add_option("project_type", _projectType)->required();
    thisCommand->add_option("project_name", _projectName);
}


void CommandInit::run()
{
	if (CPPack::hasProjectFilePath)
	{
		std::cout << "A project configuration file was found. Cannot create another" << std::endl;
		return;
	}

	if (_projectName.empty())
		_projectName = std::filesystem::current_path().stem().string();

	const ProjectData data = CPPack::generateDefaultProjectData(_projectName, projectTypeFromString(_projectType));
	CPPack::setupProjectEnvironment(data);

	std::cout << "Project created: " << data.name << std::endl;
}





CommandInfo::CommandInfo(CLI::App* const app) : Command(app, "info", "Prints information about the current project")
{}


void CommandInfo::run()
{
	if (!CPPack::hasProjectFilePath)
	{
		std::cout << "Couldn't find a project configuration file" << std::endl;
		return;
	}

	ProjectDataManager(CPPack::projectFilePath).print();
}
