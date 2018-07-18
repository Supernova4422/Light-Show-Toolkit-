
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

#ifdef __arm__
	#warning Compiling for Raspberry PI, errors may occur on other platforms
	#include "RF24.h"
	#include "MiLightRadio.h"
	#include "PL1167_nRF24.h"
	#include "RF24_Sender.h"
	#include "utility/RPi/spi.h"
#endif




int main()
{
	GroupManager manager;
	int threshhold = 10;
#ifdef __arm__
	#warning Injecting GPIO based lights into program, sudo will be needed to run
	manager.AddLight(new RF24_Sender());
	manager.AddLight(new BinaryLight(new BinLight_SYSFS(), threshhold, 0));
#endif 
	manager.AddLight(new Milight(threshhold));
	manager.AddLight(new ConsoleLight());

    SongPlayer Player = SongPlayer(manager);
    CommandLineInterface CLI(Player);

    int num;
    std::cin >> num;

}
