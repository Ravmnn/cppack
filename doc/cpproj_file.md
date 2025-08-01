Every *cppack* project must have a `*.cpproj` file, which stores information about the project. The file itself is just a JSON file. Inside it, you can fully customize and configure the way your project should be handled by *cppack*. Here's a complete list of all settings currently available:

```json
{
    // .cpproj template file

    // name of the project.
    "name": "cppack",

    // executable, static-library or shared-library.
    "type": "static-library",

    // path to the directory storing the .cpp/.c files.
    "source_directory": "src",

    // path to the directory storing the .hpp/.h files.
    // if not defined, "source_directory" will be used.
    "header_directory": "include",

    // name of the directory to be used for storing build files
    "build_directory": "build,

    // additional paths for searching for .hpp/.h files.
    "additional_include_paths": [],

    // additional paths for searching for libraries: .so/.a
    "additional_library_paths": [],

    // additional library names to link with
    "additional_libraries": [],

    // the compiler to use
    "language_compiler": "clang++",

    // 11, 14, 17, 20, 23... any valid C++ version number
    "language_version": 17,

    // current build setting to use when building.
    "current_build_setting": "debug",

    // build settings containing data that tell the compiler how to
    // compile the project.
    "build_settings": [
        {
            // the name of the build setting
            "name": "debug",

            // none, low, medium, high, extreme, shrink, extreme_shrink, debug
            //  -O0, -O1,    -O2,  -O3,  -Ofast,    -Os,            -Oz,   -Og
            "optimization": "debug",

            // none, normal,   all,    extra
            //   -w,         -Wall,   (-Wall and -Wextra)
            "warning": "normal",

            // macros to be defined.
            "defines": ["HELLO=\"hello, world\"", "DEBUGMODE"],

            // additional options passed to the compiler.
            "additional_options": ""
        },
        {
            "name": "release",
            "optimization": "high",
            "warning": "none"
        }
    ]
}

```
