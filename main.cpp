// my first program in C++
#include <iostream>
#include <string>
#include "CommandDataTypes.cpp"
#include "FileReader.h"
#include "CommandFactory.h"
#include "ProgrammableLight.h"
#include "LightShowFileReader.h"
#include "Milight.h"
#include "ConsoleLight.h"
#include "SongPlayer.h"
#include "GroupManager.h"

int main()
{
    
    LightShowFileReader Reader;
    CommandFactory Factory; 
    
    std::map<std::string, std::vector<std::string>> IntermediateFile = Reader.ProcessFile("example.txt");
    
    std::map<std::string, std::vector<Command>> ParsedFile = Factory.CreateFunctionHolder(IntermediateFile);

    SongPlayer Player; 
    Player.ParsedFile = ParsedFile;
    
    Player.RunFunction("Play");
  
    int num;
    std::cin >> num;
}