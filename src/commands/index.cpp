#include <commands/index.hpp>

#include <package/global_index.hpp>



CommandIndexRegister::CommandIndexRegister(Project* const project, CLI::App* const app)
	: Command(project, app, "register", "Registers a new package to the global index")
{
	_packagePath = ".";
	thisCommand->add_option("packagePath", _packagePath);
}


void CommandIndexRegister::run()
{
	GlobalPackageIndex::registerPackage(Project(_packagePath));
}





CommandIndexUnregister::CommandIndexUnregister(Project* const project, CLI::App* const app)
	: Command(project, app, "unregister", "Unregisters a package from the global index")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandIndexUnregister::run()
{
	GlobalPackageIndex::unregisterPackage(_packageName);
}





CommandIndexList::CommandIndexList(Project* const project, CLI::App* const app)
	: Command(project, app, "list", "Lists all registered packages")
{}


void CommandIndexList::run()
{
	for (const auto& package : fs::directory_iterator(CPPack::cppackIndexDirectoryPath))
		std::cout << package.path().stem().string() << std::endl;
}
