 
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
    
    SongPlayer Player; 
    CommandLineInterface CLI(Player);
    
    //Player.AddParsedFileToSupportFile(Parser.ParseFile("SupportFile_V1.txt"));
    
    //Player.StartPlaying("Play" , "SONG");
  
    int num;
    std::cin >> num;
    
}