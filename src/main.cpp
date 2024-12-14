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
    Project currentProject(fs::current_path());

    CLI::App* const project = app.add_subcommand("project", "Subcommands for handling a project");

    new CommandProjectInit(&currentProject, project);
    new CommandProjectInfo(&currentProject, project);
    new CommandProjectBuild(&currentProject, project);
    new CommandProjectRun(&currentProject, project);
    new CommandProjectClean(&currentProject, project);

    CLI::App* const index = app.add_subcommand("index", "Subcommands for handling the cppack global package index");

    new CommandIndexRegister(&currentProject, index);
    new CommandIndexUnregister(&currentProject, index);
    new CommandIndexList(&currentProject, index);

    CLI::App* const package = app.add_subcommand("package", "Subcommands for handling the project package dependencies");

    new CommandPackageAdd(&currentProject, package);
    new CommandPackageRemove(&currentProject, package);
    new CommandPackageList(&currentProject, package);


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
