#include <iostream>
#include <string>
#include <fstream>
#include <array>

enum operations
{
    HELP,
    RUNCMAKE,
    RUNMAKE,
    RUNPROGRAM,

    SETEXECUTABLEPATH,
    SETCMAKECOMMAND,
    SETMAKEPATH
};

enum pathIndex
{
    EXECUTABLEPATH,
    CMAKECOMMAND,
    MAKEPATH
};

void print_help()
{
    std::cout << std::endl <<
    "-- Subcommands --" << std::endl <<
    "help --> Displays this subcommand list."
    << std::endl <<
    "runcmake --> Runs the CMake command given. Spits out an error if no CMake command is set."
    << std::endl <<
    "runmake --> Runs the makefile on the path given. Spits out an error if no makefile path is set."
    << std::endl <<
    "runprogram --> Runs the executable on the path given. Spits out an error if no executable path is set."
    << std::endl <<
    "setexecutablepath <path-to-executable> --> Sets the executable path for the runprogram subcommand."
    << std::endl <<
    "setcmakecommand <cmake-command> --> Sets the CMake command for the runcmake subcommand."
    << std::endl <<
    "setmakepath <path-to-makefile> --> Sets the makefile path for the runmake subcommand."
    << std::endl;
}

int main(int argc, char* argv[])
{
    int currentOperation;

    std::array<std::string, 3> paths;

    std::fstream configFile;
    configFile.open("runnerconfig.txt");
    if (!configFile.is_open())
    {
        std::cerr << "-- Error: Cannot open file. -- " << std::endl;
        return EXIT_FAILURE;
    }

    if (argc == 1)
    {
        std::cerr << "--- Error: Please choose from these subcommands ---" << std::endl;
        currentOperation = HELP;
    }

    if (currentOperation != HELP)
    {
        if (argv[1] == "help")
            currentOperation = HELP;
        if [argv[1] == "setexecutablepath"]
        {
            
        }
    }

    switch (currentOperation)
    {
        case HELP:
            print_help();
            break;



    }
}