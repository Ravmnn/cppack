## Table of Contents

- [About](#about)
- [Usage](#usage)
- [License](#license)
- [Dependencies](#dependencies)
- [Building](#building)

## About

*cppack* is a simple command line tool made in C++ for handling C++ projects in a more user-friendly way, without the need of directly editing a Makefile or using CMake for compiling it.

- **NodeJS** -> *NPM* (Node Package Manager)
- **Lua** -> *Luarocks*
- **Ruby** -> *Rubygems*
- **Rust** -> *Cargo*
- **C#** -> *.NET* command line tool *`dotnet`*
- **C++**:
    * **Make**: Hard coded script files, tends to become unreadable as it scales. Powerfull though.
    * **CMake**: Usually hard coded, comes with a GUI. More powerfull and complete than Make; better than hard coding a Makefile, but still have a considerably long learning curve.
    * **cppack**: Very simpler command line tool for handling C++ projects. Uses Makefiles under the hood. No need for hard coding nothing. Fully configurable via a `.cpproj` file. May not be as flexible as Make or CMake though.

It supports basic project handling features, project building (compilation), dependency management and a configuration file so that you can fully customize your project settings.

## Usage

Check [The Documentation](./doc) for more information.

## License

This project is under the GNU GPLv3 license.

## Dependencies

This project uses the following libraries as dependencies:

- [CLI11](https://github.com/CLIUtils/CLI11/): Command parser library
- [nlohmann/json](https://github.com/nlohmann/json/): JSON file parser library

## Building

Currently, the only easy way of compiling *cppack* is to use *cppack*
itself, so you would need to install the already compiled version of it, then compile the project. Support for using GNU Make will come soon.
