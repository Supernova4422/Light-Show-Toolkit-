
// my first program in C++

#define HAVE_STRUCT_TIMESPEC
#define STRUCT_TIMESPEC_HAS_TV_SEC

#include "config.h"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include "CommandLineInterface.h"

void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    CommandLineInterface::RUNNING = false;
#if USING_SDL == 1
    SDL_Quit();
#endif
    exit(signum);
}

int main(int argc, char *argv[])
{
    std::unique_ptr<CommandLineInterface> cli = std::make_unique<CommandLineInterface>();
    if (argc > 1)
    {
        for (auto i = 1; i < argc - 1; i += 2)
        {
            std::cout << std::endl;

            std::cout << "Command: " << std::string(argv[i]) << ", parameter: " << std::string(argv[i + 1]) << std::endl;

            cli->ParseLine(std::string(argv[i]) + std::string(" ") + std::string(argv[i + 1]));
        }
    }
    else
    {
        cli->Run();
    }

#if USING_SDL == 1
    SDL_Quit();
#endif
    return 0;
}
