
// my first program in C++


#define HAVE_STRUCT_TIMESPEC
#define STRUCT_TIMESPEC_HAS_TV_SEC



#include <stdint.h>
#include <iostream>
#include <vector>
#include <sstream>      // std::istringstream
#include <string>
#include "CommandDataTypes.cpp"
#include "CommandFactory.h"
#include "ProgrammableLight.h"

#include "Milight.h"
#include "ConsoleLight.h"
#include "SongPlayer.h"
#include "GroupManager.h"
#include "CommandLineInterface.h"
#include "BinaryLight.h"
#include "BinaryLightController.h"
#include "BinLight_SYSFS.h"
#include <chrono>
#include "SDL_Light.h"

#ifdef __arm__
	#warning Compiling for Raspberry PI, errors may occur on other platforms
	#define RaspberryPi
	#include "RF24_Factory.h"
    #include "Factory_433.h"
#endif

SongPlayer* makePlayer() {
		GroupManager* manager = new GroupManager();
		int threshhold = 10;
#ifdef __arm__
		#warning Injecting GPIO based lights into program, sudo will be needed to run
			RF24_Factory factory;
		Factory_433 factory_rf;
		manager->AddLight(factory.get_light());
		manager->AddLight(factory_rf.get_light());
#endif
		//manager->AddLight(new Milight(threshhold));
		manager->AddLight(new ConsoleLight());

		//SDL_Light* sdl_window = new SDL_Light();
		//manager->AddLight(sdl_window);
		//manager->AddTickListener(sdl_window);

		SongPlayer* Player = new SongPlayer(manager);
		return Player;
	}
CommandLineInterface* makeInterface() {

		CommandLineInterface* CLI = new CommandLineInterface(makePlayer());
		return CLI;
}

int main(int argc, char* argv[])
{
	if (argc >= 2) {
		std::cout << "Loading file: " << argv[1] << std::endl;
		SongPlayer* Player = makePlayer();
		Player->LoadMainFile(argv[1]);
		for (int i = 3; i < argc; i++) {
			int support_file_iter = i;
			Player->AddSupportFile(argv[i]);
			std::cout << "Loading support file: " << argv[i] << std::endl;
		}
		std::cout << "Playing song:" << argv[2] << std::endl;
		Player->StartPlaying(argv[2]);
	} else {
		CommandLineInterface* cli = makeInterface();
		cli->Run();
	}
	
	return 0;
}

