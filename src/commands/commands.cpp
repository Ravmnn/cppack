#include <commands/commands.hpp>

#include <cppack/cppack.hpp>
#include <cppack/cppack_exceptions.hpp>



CommandInit::CommandInit(CLI::App* const app) : Command(app, "init", "Creates a new project")
{
	thisCommand->add_option("project_type", _projectType)->required();
    thisCommand->add_option("project_name", _projectName);
}


void CommandInit::run()
{
	InvalidProjectHandlingException::throwIfHasProjectFile();

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
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	ProjectDataManager(CPPack::projectFilePath).print();
}





CommandBuild::CommandBuild(CLI::App* const app) : Command(app, "build", "Builds the project")
{}


void CommandBuild::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	CPPack::buildProject(ProjectDataManager(CPPack::projectFilePath).get_data());
}
