## Table of Contents

- [What is a Project?](#what-is-a-project)
- [Basic Project Commands](#basic-project-commands)
    * [Creating a New Project](#creating-a-new-project)
    * [Building/Running a Project](#buildingrunning-a-project)
    * [Adding/Removing a Package or a Dependency](#addingremoving-a-package-or-a-dependency)

## What is a Project?

A project is any directory containing a [`*.cpproj`](/doc/cpproj_file.md) file (or just "project file"). Every subdirectory inside that folder becomes part of the project, so if you run *cppack* inside any of those subdirectories, *cppack* will be able to find that project file. Most of *cppack*'s operations reads or writes to that file to perfom a specific task, like building you project, adding a dependency or registering your project as a global package in the [Global Package Index](/doc/packages.md).

## Basic Project Commands

The *cppack's* subcommand responsible for project operations is the `cppack project` command. Run `cppack project --help` for a complete list of subcommands with their respective descriptions.

### Creating a New Project

To create a new project, everything you need to do is to add a project file to an already existing directory. The subcommand you can use for auto-generating a project file is `cppack project init [projectType] [projectName]?`. `[projectType]` is the type of the project. Currently, only three types are supported:

- `executable`: compiles to an executable binary file.
- `static-library`: compiles to a static library file `*.a`.
- `shared-library`: compiles to a shared library (aka dynamic library) `.so`.

`[projectName]?` is the name of the project. It's optional and if not explicitly defined, the name of the parent directory will be used.
Make sure to run this subcommand inside the directory you wanna generate the file.

Full command example: `cppack project init static-library myprojectname`

### Building/Running a Project

To run or build a project, you can use the subcommands `cppack project build` and `cppack project run`, respectively. Note that if your project is library, it can't be directly runned. For more information about the building process, see [Building](/doc/building.md).

### Adding/Removing a Package or a Dependency

Currently, *cppack's* features for managing dependencies are limited and the main feature for doing so is by using packages. If your dependency can't currently be represented by *cppack*'s types of projects, you still may be able to build your project. For more information, see [Limitations](/doc/limitations.md). However, if your dependency can be represented as a *cppack* project, you can register it as a package and use it as a dependency without any problems. For more information about registering packages, see [Packages](/doc/packages.md)

For adding or removing a package to your project, you can use the commands `cppack package add [packageName]` and `cppack package remove [packageName]`, respectively.