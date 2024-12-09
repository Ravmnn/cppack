#include <commands/project.hpp>

#include <cppack/cppack.hpp>
#include <cppack/cppack_exceptions.hpp>



CommandProjectInit::CommandProjectInit(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "init", "Creates a new project")
{
	thisCommand->add_option("projectType", _projectType)->required();
    thisCommand->add_option("projectName", _projectName);
}


void CommandProjectInit::run()
{
	InvalidProjectHandlingException::throwIfHasProjectFile();

	const ProjectData data = CPPack::generateDefaultProjectData(_projectName, projectTypeFromString(_projectType));
	CPPack::setupProjectEnvironment(data);

	std::cout << "Project created: " << data.name << std::endl;
}





CommandProjectInfo::CommandProjectInfo(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "info", "Prints information about the current project")
{}


void CommandProjectInfo::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	ProjectDataManager(cppack->getData()).print();
}





CommandProjectBuild::CommandProjectBuild(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "build", "Builds the project")
{}


void CommandProjectBuild::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	cppack->buildProject();
}





CommandProjectRun::CommandProjectRun(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "run", "Runs the project, if possible")
{}


void CommandProjectRun::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	cppack->runProject();
}





CommandProjectClean::CommandProjectClean(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "clean", "Deletes build files")
{}


void CommandProjectClean::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	std::cout << "Removing build directory" << std::endl;

	cppack->cleanProject();
}
