// my first program in C++
#include <iostream>
#include <string>
#include "FileReader.h"
#include "CommandFactory.h"

int main()
{
    
    LightShowFileReader Reader;
    CommandFactory Factory; 
    std::map<std::string, std::vector<Command>> FunctionsToPlay;
    std::map<std::string, std::vector<std::string>> IntermediateFile = Reader.ProcessFile("example.txt");
    
    for (std::map<string, vector<std::string>>::iterator it = IntermediateFile.begin(); it != IntermediateFile.end(); ++it) {
        int value = it->second.size();
        Command CommandsInFunction[5];
        int i = 0; 
        vector<Command> Commands;
        for (string Entry : it->second) {
            Commands.push_back(Factory.ParseCommand(Entry));
        }        
        FunctionsToPlay.insert(std::pair<std::string, vector<Command>>(it->first,Commands));
    }
        CommandFactory Factory.ConvertFunctionNamesToFunctionPointer(FunctionsToPlay);
    



}