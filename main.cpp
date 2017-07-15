 
// my first program in C++
#include <stdint.h>
#include <iostream>
#include <vector>
#include <sstream>      // std::istringstream
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
    
    std::string hex_chars("6A");
    uint8_t d = (uint8_t) std::stoi(hex_chars, nullptr , 16);
    std::cout <<  d << std::endl;

    LightShowFileReader Reader;
    CommandFactory Factory; 
    
    std::map<std::string, std::vector<std::string>> IntermediateFile = Reader.ProcessFile("example.txt");
    
    std::map<std::string, std::vector<Command>> ParsedFile = Factory.CreateFunctionHolder(IntermediateFile);

    std::map<std::string, std::vector<std::string>> SupportFileIntermediate = Reader.ProcessFile("SupportFile_V1.txt");
    
    std::map<std::string, std::vector<Command>> SupportFileParsed = Factory.CreateFunctionHolder(SupportFileIntermediate);
    
    SongPlayer Player; 
    Player.MainFile = ParsedFile;
    Player.AddParsedFileToSupportFile(SupportFileParsed);
    
    Player.RunFunction("Play");
  
    int num;
    std::cin >> num;
    
}