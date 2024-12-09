#include <cppack/cppack.hpp>
#include <cppack/exception.hpp>
#include <commands/commands.hpp>



int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");
    app.require_subcommand();


    new CommandInit(&app);
    new CommandInfo(&app);
    new CommandBuild(&app);
    new CommandRun(&app);
    new CommandClean(&app);

    CPPack::init(std::filesystem::current_path());

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
