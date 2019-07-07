#include <string>
#include <iostream>
#include <algorithm>
#include "CommandLineInterface.h"

bool CommandLineInterface::RUNNING = true;

CommandLineInterface::CommandLineInterface()
{
    this->Player = std::make_unique<SongPlayer>();
    std::cout << "CommandLine Interface has loaded" << std::endl;
    std::cout << "Type 'Help' to get started." << std::endl;

    userCommands.push_back(UserCommand("loadmain", "Load the Lighshow file by passing as a parameter",
                                       [&](std::string afterSpace) {
                                           Player->LoadMainFile(afterSpace);
                                           std::cout << "Loaded Main File" << std::endl;
                                       }));

    userCommands.push_back(UserCommand("run", "To start playing the file alongside a song, pass the music file name as a parameter",
                                       [&](std::string afterSpace) {
                                           std::cout << "Starting Song" << std::endl;
                                           Player->PrepareSong(afterSpace);
                                           Player->StartPlaying();
                                           std::cout << "Finished Playing" << std::endl;
                                       }));

    userCommands.push_back(UserCommand("skip", "Starts the song with a delay",
                                       [&](std::string afterSpace) {
                                           Player->SetSongStart(std::stoi(afterSpace));
                                           std::cout << "Added skip" << std::endl;
                                       }));

    userCommands.push_back(UserCommand("loadsdl", "Loads a GUI window",
                                       [&](std::string afterSpace) {
                                           Player->add_sdl();
                                           std::cout << "Loaded SDL" << std::endl;
                                       }));

    userCommands.push_back(UserCommand("loadsupport", "Loads a second song file, that can be referenced by the first one loaded",
                                       [&](std::string afterSpace) {
                                           Player->AddSupportFile(afterSpace);
                                           std::cout << "Loaded Support File" << std::endl;
                                       }));
    userCommands.push_back(UserCommand("runmp3", "Loads and runs a .ls and .mp3 file with a given filename",
                                       [&](std::string afterSpace) {
                                           std::cout << "Loading file and mp3" << std::endl;
                                           Player->LoadMainFile(afterSpace + ".ls");
                                           Player->PrepareSong(afterSpace + ".mp3");
                                           Player->StartPlaying();
                                           std::cout << "Finished Playing" << std::endl;
                                       }));

    userCommands.push_back(UserCommand("startat", "When the run command is executed, the song will not begin until the time given (as a parameter) has passed",
                                       [&](std::string afterSpace) {
                                           unsigned int hours = ((afterSpace[0] - '0') * 10) + (afterSpace[1] - '0');
                                           unsigned int minutes = ((afterSpace[3] - '0') * 10) + (afterSpace[4] - '0');
                                           Player->SetTime(hours, minutes);
                                       }));

    userCommands.push_back(UserCommand("help", "Gives the current time",
                                       [&](std::string afterSpace) {
                                           std::cout << "For more information, visit: https://github.com/Fantasmos/Light-Show-Toolkit-" << std::endl;
                                           std::cout << "Input syntax is: <Command> <Parameter>" << std::endl;
                                           std::cout << "All commands: " << std::endl;
                                           for (auto command : userCommands)
                                           {
                                               std::cout << "    " << command.get_help() << std::endl;
                                           }
                                       }));
    userCommands.push_back(UserCommand("exit", "Exits the application",
                                       [&](std::string afterSpace) {
                                           CommandLineInterface::RUNNING = false;
                                       }));
    userCommands.push_back(UserCommand("exit", "Exits the application",
                                       [&](std::string afterSpace) {
                                           CommandLineInterface::RUNNING = false;
                                       }));
}

void CommandLineInterface::Run()
{
    std::string Line;
    unsigned int consecutive_blanks = 0;
    unsigned int consecutive_blanks_limit = 5;

    do
    {
        if (Line != "")
        {
            std::cout << std::endl;
            std::cout << "Waiting on Input:" << std::endl;
        }

        std::getline(std::cin, Line);

        if (Line == "")
        {
            ++consecutive_blanks;
        }
        else
        {
            ParseLine(Line);
            Player->On_Tick();
            consecutive_blanks = 0;
        }
    } while (CommandLineInterface::RUNNING && consecutive_blanks < consecutive_blanks_limit);
}

void CommandLineInterface::ParseLine(std::string Line)
{
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

    for (auto command : userCommands)
    {
        if (command.input_matches(BeforeSpace))
        {
            command.run(AfterSpace);
        }
    }
    std::cout << std::endl;
}
