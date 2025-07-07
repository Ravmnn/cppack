#include <commands/project.hpp>

#include <project/project_exceptions.hpp>



CommandProjectInit::CommandProjectInit(Project* const project, CLI::App* const app)
	: Command(project, app, "init", "Creates a new project")
{
	thisCommand->add_option("projectType", _projectType)->required();
    thisCommand->add_option("projectName", _projectName);
}


void CommandProjectInit::run()
{
	InvalidProjectHandlingException::throwIfHasProjectFile();

	const ProjectData data = CPPack::generateDefaultProjectData(_projectName, projectTypeFromString(_projectType));
	CPPack::setupProjectEnvironment(data);
}





CommandProjectInfo::CommandProjectInfo(Project* const project, CLI::App* const app)
	: Command(project, app, "info", "Prints information about the current project")
{}


void CommandProjectInfo::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	ProjectDataManager(project->getData()).print();
}





CommandProjectBuild::CommandProjectBuild(Project* const project, CLI::App* const app)
	: Command(project, app, "build", "Builds the project")
{}


void CommandProjectBuild::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->buildProject();
}





CommandProjectRun::CommandProjectRun(Project* const project, CLI::App* const app)
	: Command(project, app, "run", "Runs the project, if possible")
{}


void CommandProjectRun::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->runProject();
}





CommandProjectClean::CommandProjectClean(Project* const project, CLI::App* const app)
	: Command(project, app, "clean", "Deletes build files")
{}


void CommandProjectClean::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->cleanProject();
}





CommandProjectMakefy::CommandProjectMakefy(Project* const project, CLI::App* const app)
	: Command(project, app, "makefy", "Generates an independent Makefile system")
{}


void CommandProjectMakefy::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->makefyProject();
}
