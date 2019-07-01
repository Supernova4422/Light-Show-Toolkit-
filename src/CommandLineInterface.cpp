#include "CommandLineInterface.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "SDL_Light.h"

CommandLineInterface::CommandLineInterface()
{
    this->Player = std::make_unique<SongPlayer>();
    std::cout << "CommandLine Interface has loaded" << std::endl;
    std::cout << "Type 'Help' to get started." << std::endl;
}

void CommandLineInterface::Run()
{
    bool Running = true;
    while (Running)
    {
        std::cout << std::endl;
        std::cout << "Waiting on Input" << std::endl;
        std::string Line;
        std::getline(std::cin, Line);
        ParseLine(Line);
        Player->On_Tick();
    }
}

void CommandLineInterface::ParseLine(std::string Line)
{
    std::string LoadMainCommand = "loadmain";
    std::string delayCommand = "skip";
    std::string LoadSupportCommand = "loadsupport";
    std::string MP3ShowCommand = "mp3show";
    std::string RunCommand = "run";
    std::string PrintMainDataCommand = "printMainData";
    std::string PrintSupportDataCommand = "printSupportData";
    std::string loadSdlCommand = "sdlload";
    std::string Help = "help";
    std::string now = "now";

    std::string BeforeSpace = "";
    std::string AfterSpace = "";

    bool EncounteredFirstSpace = false;

    for (char c : Line)
    {
        if (EncounteredFirstSpace)
        {
            AfterSpace = AfterSpace + c;
        }
        else
        {
            if (c == ' ')
            {
                EncounteredFirstSpace = true;
            }
            else
            {

                BeforeSpace = BeforeSpace + char(::tolower(c));
            }
        }
    }

    std::cout << std::endl;

    if (BeforeSpace == delayCommand)
    {
        Player->SetSongStart(std::stoi(AfterSpace));
        std::cout << "Added skip" << std::endl;
    }
    if (BeforeSpace == now)
    {
        unsigned int hours   = ((AfterSpace[0] - '0') * 10) + (AfterSpace[1] - '0');
        unsigned int minutes = ((AfterSpace[3] - '0') * 10) + (AfterSpace[4] - '0');
        unsigned int seconds = ((AfterSpace[6] - '0') * 10) + (AfterSpace[7] - '0');
        Player->SetTime(hours,minutes,seconds);
    }
    if (BeforeSpace == loadSdlCommand)
    {
        Player->add_sdl();
        std::cout << "Loaded SDL" << std::endl;
    }
    if (BeforeSpace == LoadMainCommand)
    {
        Player->LoadMainFile(AfterSpace);
        std::cout << "Loaded Main File" << std::endl;
    }
    if (BeforeSpace == LoadSupportCommand)
    {
        Player->AddSupportFile(AfterSpace);
        std::cout << "Loaded Support File" << std::endl;
    }
    if (BeforeSpace == MP3ShowCommand)
    {
        std::cout << "Loading file and mp3" << std::endl;
        Player->LoadMainFile(AfterSpace + ".ls");
        Player->PrepareSong(AfterSpace + ".mp3");
        Player->StartPlaying();
        std::cout << "Finished Playing" << std::endl;
    }
    if (BeforeSpace == RunCommand)
    {
        std::cout << "Starting Song" << std::endl;
        Player->PrepareSong(AfterSpace);
        Player->StartPlaying();
        std::cout << "Finished Playing" << std::endl;
    }

    if (BeforeSpace == Help)
    {
        std::cout << "For more information, visit: https://github.com/Fantasmos/Light-Show-Toolkit-" << std::endl
                  << std::endl;
        std::cout << "Guide to usage:" << std::endl;
        std::cout << "  Load the Lighshow file with: LoadMain FILENAME.ls" << std::endl;
        std::cout << "  Load any secondary files with: LoadSupport FILENAME" << std::endl;
        std::cout << "  To start playing the file alongside a song, use: RUN MusicFileName" << std::endl;
    }
}
