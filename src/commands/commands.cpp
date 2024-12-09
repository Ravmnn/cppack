#include <commands/commands.hpp>

#include <cppack/cppack.hpp>
#include <cppack/cppack_exceptions.hpp>



CommandInit::CommandInit(CLI::App* const app) : Command(app, "init", "Creates a new project")
{
	thisCommand->add_option("projectType", _projectType)->required();
    thisCommand->add_option("projectName", _projectName);
}


void CommandInit::run()
{
	InvalidProjectHandlingException::throwIfHasProjectFile();

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

	CPPack::buildProject(CPPack::getProjectDataFromCurrentProject());
}





CommandRun::CommandRun(CLI::App* const app) : Command(app, "run", "Runs the project, if possible")
{}


void CommandRun::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	CPPack::runProject(CPPack::getProjectDataFromCurrentProject());
}





CommandClean::CommandClean(CLI::App* const app) : Command(app, "clean", "Deletes build files")
{}


void CommandClean::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	CPPack::cleanProject(CPPack::getProjectDataFromCurrentProject());
}
