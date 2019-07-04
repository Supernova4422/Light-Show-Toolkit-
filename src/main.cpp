
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
#include "SongPlayer.h"
#include "CommandLineInterface.h"

#ifdef __arm__
#warning Compiling for Raspberry PI, errors may occur on other platforms
#define RaspberryPi
#include "RF24_Factory.h"
#include "Factory_433.h"
#endif


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

	return 0;
}
