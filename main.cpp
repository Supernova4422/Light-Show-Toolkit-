 
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
    
    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::cout << "printing out 1000 stars...\n";
    for (int i=0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double, std::milli> time_span = t2 - t1;

    std::cout << "It took me " << time_span.count() << " milliseconds.";
    std::cout << std::endl;




    SongPlayer Player; 
    CommandLineInterface CLI(Player);
    

    //Player.AddParsedFileToSupportFile(Parser.ParseFile("SupportFile_V1.txt"));
    
    //Player.StartPlaying("Play" , "SONG");
  
    int num;
    std::cin >> num;
    
}