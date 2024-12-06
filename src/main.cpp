#include <project_data.hpp>
#include <commands/commands.hpp>



int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");
    app.require_subcommand();


    new CommandInit(&app);
    new CommandInfo(&app);


    CLI11_PARSE(app, argc, argv)


    return 0;
}
