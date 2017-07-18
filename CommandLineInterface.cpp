#include "CommandLineInterface.h"
#include <string>
#include <iostream>

CommandLineInterface::CommandLineInterface(SongPlayer &Player) {
    bool Running = true;
    this->Player = &Player;
    while (Running) {
        std::cout << "Waiting on Input" << std::endl;
        std::string Line;
        std::getline(std::cin, Line);
        ParseLine(Line);
    }
}


void CommandLineInterface::ParseLine (std::string Line) {
    std::string LoadMainCommand = "LoadMain";
    std::string LoadSupportCommand = "LoadSupport";
    std::string RunCommand = "Run";
    std::string PrintMainDataCommand = "PrintMainData";
    std::string PrintSupportDataCommand = "PrintSupportData";
    std::string Help = "Help";
    
    
    std::string BeforeSpace = "";
    std::string AfterSpace = "";

    bool EncounteredFirstSpace = false;
    
    for (char c : Line)
    {
        if (EncounteredFirstSpace) {
            AfterSpace = AfterSpace + c;
        } else {
            if (c == ' ')
            {
                EncounteredFirstSpace = true;
            } else {
                BeforeSpace = BeforeSpace + c;
            }
        }
    }
    
    if (BeforeSpace == LoadMainCommand) {
        
        Player->LoadMainFile(AfterSpace);
    } 
    if (BeforeSpace == LoadSupportCommand)
    {
        Player->AddSupportFile(AfterSpace);
    }
    if (BeforeSpace == RunCommand)
    {
        std::string Play = "Play";
        Player->StartPlaying(Play, AfterSpace);
    }
    if (BeforeSpace == PrintMainDataCommand) {
    } 
    if (BeforeSpace == PrintSupportDataCommand) {
    }     
    
   
}

