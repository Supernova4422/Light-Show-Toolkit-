
// my first program in C++

#define HAVE_STRUCT_TIMESPEC
#define STRUCT_TIMESPEC_HAS_TV_SEC

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
	if (argc >= 2)
	{
		std::cout << "Loading file: " << argv[1] << std::endl;
		std::unique_ptr<SongPlayer> Player = std::make_unique<SongPlayer>();
		Player->LoadMainFile(argv[1]);

		for (int i = 3; i < argc; i++)
		{
			Player->AddSupportFile(argv[i]);
			std::cout << "Loading support file: " << argv[i] << std::endl;
		}

		std::cout << "Playing song:" << argv[2] << std::endl;
		Player->StartPlaying(argv[2]);
	}
	else
	{
		std::unique_ptr<CommandLineInterface> cli = std::make_unique<CommandLineInterface>();
		cli->Run();
	}

	return 0;
}
