#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>

const std::string CONFIGPATH = "runnerconfig.txt";

enum operations
{
    HELP,
    RUNCMAKE,
    RUNMAKE,
    RUNPROGRAM,

    SETEXECUTABLEPATH,
    SETCMAKECOMMAND,
    SETMAKEDIR
};

enum pathIndex
{
    EXECUTABLEPATH,
    CMAKECOMMAND,
    MAKEDIR
};

void print_help()
{
    std::cout <<
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
    "setmakedir <path-to-makefile-directory> --> Sets the makefile directory for the runmake subcommand."
    << std::endl;
}

void openFile(std::fstream& file, std::string path, bool trunc)
{
    if (!trunc)
    {
        file.open(path);
        if (!file.is_open())
        {
            std::cerr << "-- Error: Cannot open file. -- " << std::endl;
            std::exit(-1);
        }
    }
    else
    {
        file.open(path, std::ios::in | std::ios::out | std::ios::trunc);
        if (!file.is_open())
        {
            std::cerr << "-- Error: Cannot open file. -- " << std::endl;
            std::exit(-1);
        }   
    }
}

void getLines(std::fstream& file, std::array<std::string, 3>& lines)
{
    size_t i = 0;
    while(!file.eof())
    {
        std::string temp;
        std::getline(file, temp);
        lines[i] = temp;
        ++i;
    }
}

void setContents(std::fstream &file, std::array<std::string, 3> &lines)
{
    openFile(file, CONFIGPATH, true);
    for (auto line : lines)
    {
        file << line << std::endl;
    }
    file.close();
}

int main(int argc, char* argv[])
{
    int currentOperation = -1;

    std::array<std::string, 3> paths;

    std::fstream configFile;
    openFile(configFile, CONFIGPATH, false);
    getLines(configFile, paths);
    configFile.close();

    if (argc == 1)
    {
        std::cerr << "--- Error: Please choose from these subcommands ---" << std::endl;
        currentOperation = HELP;
    }

    if (currentOperation != HELP)
    {
        if (std::string(argv[1]) == "help")
            currentOperation = HELP;
        else if (std::string(argv[1]) == "setexecutablepath")
            currentOperation = SETEXECUTABLEPATH;
        else if (std::string(argv[1]) == "setcmakecommand")
            currentOperation = SETCMAKECOMMAND;
        else if (std::string(argv[1]) == "setmakedir")
            currentOperation = SETMAKEDIR;
        else
        {
            std::cerr << "--- Error: Invalid subcommand. Run 'runner help' for help. ---" << std::endl;
            return EXIT_FAILURE;
        }
    }

    switch (currentOperation)
    {
        case HELP:
            print_help();
            break;

        case SETEXECUTABLEPATH:
            if (argc != 3)
            {
                std::cerr << "--- Error: Invalid arguments to 'setexecutablepath' subcommand. Run 'runner help' for help. ---" << std::endl;
                return EXIT_FAILURE;
            }
            paths[EXECUTABLEPATH] = argv[2];
            setContents(configFile, paths);
            break;

        case SETCMAKECOMMAND:
        {
            if (argc < 3)
            {
                std::cerr << "--- Error: Invalid arguments to 'setcmakecommand' subcommand. Run 'runner help' for help. ---" << std::endl;
                return EXIT_FAILURE;
            }

            std::stringstream command;

            for (size_t i = 2; i < argc; ++i)
            { 
                command << argv[i] << " ";
            }
            paths[CMAKECOMMAND] = command.str();
            setContents(configFile, paths);
            
        }
            break;

        case SETMAKEDIR:
            if (argc != 3)
            {
                std::cerr << "--- Error: Invalid arguments to 'setmakedir' subcommand. Run 'runner help' for help. ---" << std::endl;
                return EXIT_FAILURE;
            }
            paths[MAKEDIR] = argv[2];
            setContents(configFile, paths);
            break;
    }

    return 0;
}