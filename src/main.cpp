
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

long getDigit(char c)
{
	return (long)c - (long)'0';
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << "Beginning" << std::endl;
		std::unique_ptr<SongPlayer> Player = std::make_unique<SongPlayer>();

		for (auto i = 0; i < argc - 1; ++i)
		{
			if (std::strcmp(argv[i], "-file"))
			{
				Player->LoadMainFile(argv[++i]);
			}
			else if (std::strcmp(argv[i], "-supportfile"))
			{
				Player->AddSupportFile(argv[++i]);
			}
			else if (std::strcmp(argv[i],  "-time"))
			{
				++i;
				unsigned int hours = (getDigit(argv[i][0])  * 10) + getDigit(argv[i][1]);
				unsigned int minutes = (getDigit(argv[i][3]) * 10) + getDigit(argv[i][4]);
				unsigned int seconds = (getDigit(argv[i][6]) * 10) + getDigit(argv[i][7]);

				Player->SetTime(hours,minutes,seconds);
			}
			else if (std::strcmp(argv[i],  "-song"))
			{
				Player->PrepareSong(argv[2]);
			}
			else if (std::strcmp(argv[i], "-start"))
			{
				Player->SetSongStart(std::stoi(argv[++i]));
			}
		}
		Player->StartPlaying(argv[2]);
	}
	else
	{
		std::unique_ptr<CommandLineInterface> cli = std::make_unique<CommandLineInterface>();
		cli->Run();
	}

	return 0;
}
