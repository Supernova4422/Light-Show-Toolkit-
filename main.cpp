 
// my first program in C++


#define HAVE_STRUCT_TIMESPEC
#define STRUCT_TIMESPEC_HAS_TV_SEC
#define STRUCT_TIMESPEC_HAS_TV_NSEC


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
#include "GPIO_PI.h"
#include <chrono>
int main()
{

	GroupManager manager;
	int threshhold = 10;
	manager.AddLight(new Milight(threshhold));
	manager.AddLight(new ConsoleLight());
	manager.AddLight(new BinaryLight(threshhold, new GPIO_PI(), 0));

    SongPlayer Player = SongPlayer(manager);
    CommandLineInterface CLI(Player);
    
    int num;
    std::cin >> num;
    
}