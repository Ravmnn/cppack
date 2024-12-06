#include <CLI11.hpp>

#include <project_data.hpp>



int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");

    // bool result = false;
    // app.add_flag("-t,--test,!--no-test", result);

    // std::string val;
    // app.add_option("myopt1", val);

//    CLI11_PARSE(app, argc, argv)

    std::ifstream file("cppack.cpproj");

    ProjectDataManager data(json::parse(file));
    data.print();

    return 0;
}
