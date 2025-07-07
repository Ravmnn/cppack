#include <cppack/exception.hpp>
#include <commands/project.hpp>
#include <commands/index.hpp>
#include <commands/package.hpp>



// TODO: be able to generate fully independent Makefile system (add library dependency management).
// TODO: create a json property for the independent Makefiles directory.
// TODO: be able to temporary specify the build setting when building or running (CLI).



int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");
    app.require_subcommand();

    CPPack::init();
    Project currentProject(fs::current_path());

    CLI::App* const projectSubcommand = app.add_subcommand("project", "Subcommands for handling a project");

    new CommandProjectInit(&currentProject, projectSubcommand);
    new CommandProjectInfo(&currentProject, projectSubcommand);
    new CommandProjectBuild(&currentProject, projectSubcommand);
    new CommandProjectRun(&currentProject, projectSubcommand);
    new CommandProjectClean(&currentProject, projectSubcommand);
    new CommandProjectMakefy(&currentProject, projectSubcommand);

    CLI::App* const indexSubcommand = app.add_subcommand("index", "Subcommands for handling the cppack global package index");

    new CommandIndexRegister(&currentProject, indexSubcommand);
    new CommandIndexUnregister(&currentProject, indexSubcommand);
    new CommandIndexList(&currentProject, indexSubcommand);

    CLI::App* const packageSubcommand = app.add_subcommand("package", "Subcommands for handling the project package dependencies");

    new CommandPackageAdd(&currentProject, packageSubcommand);
    new CommandPackageRemove(&currentProject, packageSubcommand);
    new CommandPackageList(&currentProject, packageSubcommand);


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
