
// my first program in C++

#define HAVE_STRUCT_TIMESPEC
#define STRUCT_TIMESPEC_HAS_TV_SEC
#ifdef __arm__
#warning Compiling for Raspberry PI, errors may occur on other platforms
#define RaspberryPi
#define RPI
#endif

#include "config.h"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include "SongPlayer.h"
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
		for (auto i = 0; i < argc - 1; i += 2)
		{
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
