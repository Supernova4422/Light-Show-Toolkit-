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
    int Space;
    Space = Line.find(" ") + 1; 

    std::size_t Pos;
    Pos = Line.find(LoadMainCommand);
    if (Pos !=  std::string::npos) {
        
        Player->LoadMainFile(Line.substr(Space));
    } else {  
        Pos = Line.find(LoadSupportCommand);

        if (Pos != std::string::npos) {
            Player->AddSupportFile(Line.substr(Space));
        }
    
        else {
            Pos = Line.find(RunCommand);
            std::string Play = "Play";
            if (Pos != std::string::npos) {
                    Player->StartPlaying(Play, Line.substr(Space));
            }
        } 
        
        if (Line.find(PrintMainDataCommand) != std::string::npos) {
        } 
        
        if (Line.find(PrintSupportDataCommand) != std::string::npos) {
        }
    }
}

