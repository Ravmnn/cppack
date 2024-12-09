#include <utility/file.hpp>
#include <cppack/cppack.hpp>
#include <cppack/exception.hpp>
#include <commands/project.hpp>
#include <commands/index.hpp>



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
    new CommandIndexExist(&cppack, index);
    new CommandIndexList(&cppack, index);

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
