#include <commands/package.hpp>

#include <project/project_exceptions.hpp>



CommandPackageAdd::CommandPackageAdd(Project* const project, CLI::App* const app)
	: Command(project, app, "add", "Adds a new package dependency to the project")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandPackageAdd::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->addPackageDependency(_packageName);
}





CommandPackageRemove::CommandPackageRemove(Project* const project, CLI::App* const app)
	: Command(project, app, "remove", "Removes a package dependency from the project")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandPackageRemove::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	project->removePackageDependency(_packageName);
}





CommandPackageList::CommandPackageList(Project* const project, CLI::App* const app)
	: Command(project, app, "list", "Lists all package dependencies from the project")
{}


void CommandPackageList::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	for (const std::string& dependency : project->getData().dependencies)
		std::cout << dependency << std::endl;
}
