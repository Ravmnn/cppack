#include <commands/package.hpp>

#include <cppack/cppack.hpp>
#include <cppack/cppack_exceptions.hpp>



CommandPackageAdd::CommandPackageAdd(CPPack* const cppack, CLI::App* const app)
	: Command(cppack, app, "add", "Adds a new package dependency to the project")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandPackageAdd::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	cppack->addPackageDependency(_packageName);
}





CommandPackageRemove::CommandPackageRemove(CPPack* const cppack, CLI::App* const app)
	: Command(cppack, app, "remove", "Removes a package dependency from the project")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandPackageRemove::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	cppack->removePackageDependency(_packageName);
}





CommandPackageList::CommandPackageList(CPPack* const cppack, CLI::App* const app)
	: Command(cppack, app, "list", "Lists all package dependencies from the project")
{}


void CommandPackageList::run()
{
	InvalidProjectHandlingException::throwIfHasNotProjectFile();

	for (const std::string& dependency : cppack->getData().dependencies)
		std::cout << dependency << std::endl;
}
