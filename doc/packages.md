## Table of Contents

- [What are Packages](#what-are-packages)
- [Registering/Unregistering Packages](#registeringunregistering-packages)

## What are Packages

Packages are [Projects](/doc/projects.md) that are stored in the global package index. That means only directories with a project file will be interpreted as packages. The global package index is a directory where *cppack* stores all packages. It's located at `~/.cppack/index`. The main feature of packages is that they can be used as dependencies by other projects and packages. Note that only library projects can be used as packages. Using packages as dependencies is easier than handling dependencies yourself, since *cppack* handles them automatically, avoiding the need of explicitly adding include paths and manually configuring the compiler.

## Registering/Unregistering Packages

Registering a package is just a fancy name for adding it to the global package index. To do so, use the subcommand `cppack index register [packagePath]?`.

- `[packagePath]?`: The optional path for the package. If not defined, the current path will be used.

After you have registered a package, you can use it as a dependency. See [Adding/Removing a Package or a Dependency](#addingremoving-a-package-or-a-dependency).

To unregister a package, remove it from the global package index, use the subcommand `cppack index unregister [packageName]`.

- `[packageName]`: The name of the package to unregister.