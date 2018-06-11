 
// my first program in C++
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

#include <chrono>
int main()
{
	GroupManager manager;
	manager.AddLight(new Milight());
	manager.AddLight(new ConsoleLight());

    SongPlayer Player = SongPlayer(manager);
    CommandLineInterface CLI(Player);
    
    int num;
    std::cin >> num;
    
}