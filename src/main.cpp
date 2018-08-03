
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




int main(int argc, char* argv[])
{
	GroupManager manager;
	int threshhold = 10;
#ifdef __arm__
	#warning Injecting GPIO based lights into program, sudo will be needed to run
	RF24_Factory factory;
	Factory_433 factory_rf;
	manager.AddLight(factory.get_light());
	manager.AddLight(factory_rf.get_light());
#endif
	manager.AddLight(new Milight(threshhold));
	manager.AddLight(new ConsoleLight());
    manager.AddLight(new SDL_Light());

    SongPlayer Player = SongPlayer(manager);
    CommandLineInterface CLI(Player);

    int num;
    std::cin >> num;

}
