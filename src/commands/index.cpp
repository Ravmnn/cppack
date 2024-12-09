#include <commands/index.hpp>

#include <cppack/cppack.hpp>



CommandIndexRegister::CommandIndexRegister(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "register", "Registers a new package to the global index")
{
	_packagePath = ".";
	thisCommand->add_option("packagePath", _packagePath);
}


void CommandIndexRegister::run()
{
	CPPack::registerPackage(CPPack(_packagePath));
}





CommandIndexUnregister::CommandIndexUnregister(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "unregister", "Unregisters a package from the global index")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandIndexUnregister::run()
{
	CPPack::unregisterPackage(_packageName);
}





CommandIndexExist::CommandIndexExist(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "exist", "Checks if a package is registered")
{
	thisCommand->add_option("packageName", _packageName)->required();
}


void CommandIndexExist::run()
{
	std::cout << std::boolalpha << CPPack::isPackageRegistered(_packageName) << std::endl;
}





CommandIndexList::CommandIndexList(CPPack* const cppack, CLI::App* const app) : Command(cppack, app, "list", "Lists all registered packages")
{}


void CommandIndexList::run()
{
	for (const auto& package : fs::directory_iterator(CPPack::cppackIndexDirectoryPath))
		std::cout << package.path().stem().string() << std::endl;
}
