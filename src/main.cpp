#include <iostream>

#include <CLI11.hpp>


int main(int argc, char** argv)
{
    CLI::App app("User-friendly C++ project manager.", "cppack");

    bool result = false;
    app.add_flag("-t,--test,!--no-test", result);

    CLI11_PARSE(app, argc, argv)

    std::cout << result << std::endl;

    return 0;
}