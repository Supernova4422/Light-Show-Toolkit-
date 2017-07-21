#include "CommandLineInterface.h"
#include <string>
#include <iostream>

CommandLineInterface::CommandLineInterface(SongPlayer &Player) {
    bool Running = true;
    this->Player = &Player;
    std::cout << "CommandLine Interface has loaded" << std::endl;
    std::cout << "Type 'Help' to get started." << std::endl;
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
        Player->StartPlaying(AfterSpace);
    }
    if (BeforeSpace == PrintMainDataCommand) {
    } 
    if (BeforeSpace == PrintSupportDataCommand) {
    }     
    if (BeforeSpace == Help) {
        std::cout << "For more information, visit: https://github.com/Fantasmos/Light-Show-Toolkit-" << std::endl << std::endl;
        std::cout << "Guide to usage:" << std::endl;
        std::cout << "  Load the Lighshow file with: LoadMain FILENAME.ls" << std::endl;
        std::cout << "  Load any secondary files with: LoadSupport FILENAME" << std::endl;
        std::cout << "  To start playing the file alongside a song, use: RUN MusicFileName" << std::endl;
        
    } 
    
   
}

