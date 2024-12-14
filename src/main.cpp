#include <cppack/exception.hpp>
#include <commands/project.hpp>
#include <commands/index.hpp>
#include <commands/package.hpp>



// TODO: improve project data property (too much boilerplate)
// TODO: use fs::path globally to represent path strings
// TODO: code cleanup at cppack.cpp: methods getDependenciesXPaths can be improved
// TODO: generates "src/[projectname]" and "include/[projectname]"



int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");
    app.require_subcommand();

    CPPack::init();
    CPPack cppack(fs::current_path());

    CLI::App* project = app.add_subcommand("project", "Subcommands for handling a project");

    new CommandProjectInit(&cppack, project);
    new CommandProjectInfo(&cppack, project);
    new CommandProjectBuild(&cppack, project);
    new CommandProjectRun(&cppack, project);
    new CommandProjectClean(&cppack, project);

    CLI::App* index = app.add_subcommand("index", "Subcommands for handling the cppack global package index");

    new CommandIndexRegister(&cppack, index);
    new CommandIndexUnregister(&cppack, index);
    new CommandIndexList(&cppack, index);

    CLI::App* package = app.add_subcommand("package", "Subcommands for handling the project package dependencies");

    new CommandPackageAdd(&cppack, package);
    new CommandPackageRemove(&cppack, package);
    new CommandPackageList(&cppack, package);


    try
    {
    	app.parse(argc, argv);
    }
    catch (const CPPackException& err)
    {
    	std::cout << "Error: " << err.what() << std::endl;

     	return 1;
    }
    catch (const CLI::ParseError& e)
    {
    	return app.exit(e);
    }


    return 0;
}
