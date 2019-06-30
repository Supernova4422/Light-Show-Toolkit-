
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <fstream>

#include "SDL_net.h"
#include "GroupManager.h"
#include "SDL_Light.h"

void SongPlayer::add_sdl()
{
    groupManager.AddLight<SDL_Light>();
}

void SongPlayer::LoadMainFile(const std::string FileName)
{
    MainFile = Parser.ParseFile(FileName);
}

void SongPlayer::AddSupportFile(const std::string FileName)
{
    AddParsedFileToSupportFile(Parser.ParseFile(FileName));
}

void SongPlayer::AddFunctionToSupportFile(const std::string FunctionName, const std::vector<Command> Commands)
{
    SupportFile.insert(std::pair<std::string, std::vector<Command>>(FunctionName, Commands));
}

void SongPlayer::AddParsedFileToSupportFile(std::map<std::string, std::vector<Command>> ParsedFile)
{
    for (auto item : ParsedFile)
    {
        AddFunctionToSupportFile(item.first, item.second);
    }
}

void SongPlayer::RunFunction(const std::string FunctionToPlay, const CommandOperation Operation)
{
    auto search = MainFile.find(FunctionToPlay);

    if (search == MainFile.end()) //Error, didn't find the function
    {
        search = SupportFile.find(FunctionToPlay);
        if (search == SupportFile.end())
        {           //Error didn't find the function
            return; //Return to break the cycle
        }
    }

    //Due to the return statement above, this is only reachable if we find a function
    for (Command item : search->second)
    {
        if (Operation != CommandOperation::set)
        {
            Command CommandTempItem = item;
            CommandTempItem.Operation = Operation;
            RunCommand(CommandTempItem);
        }
        else
        {
            RunCommand(item);
        }
    }
}
void SongPlayer::RunCommand(const Command item)
{
    //Make into seperate function to make recursive
    if (item.type == CommandType::Wait)
    {
        double timetowait = std::atof(item.value.c_str());
        WaitMilliseconds((int)(timetowait * 1000));
    }
    else
    {
        if (item.type == CommandType::SpecificCommand)
        {
            groupManager.SpecificCommand(item);
        }

        if (item.type == CommandType::Group)
        {
            groupManager.SetGroups(atoi(item.value.c_str()), item);
        }

        if (item.type == CommandType::FunctionName)
        {
            for (size_t i = 0; i < item.TimesToExecute; i++)
            {
                RunFunction(item.value, item.Operation);
            }
        }

        if (item.type == CommandType::ColourChange_RGB)
        {
            Colour Newcolour(item.value, true);
            groupManager.UpdateColour(Newcolour, item);
        }

        if (item.type == CommandType::ColourChange_HSV)
        {
            Colour Newcolour(item.value, false);
            groupManager.UpdateColour(Newcolour, item);
        }
    }
    //groupManager.On_Tick();
}

void SongPlayer::WaitMilliseconds(const int milliseconds)
{
    std::cout << "Starting wait for: " << milliseconds << " Milliseconds" << std::endl;
    WaitTimeTotalInMilli = WaitTimeTotalInMilli + milliseconds;

    std::this_thread::sleep_until(SongStartTime + std::chrono::milliseconds(WaitTimeTotalInMilli));

    std::cout << "Finished Waiting" << std::endl;
}

void SongPlayer::StartPlaying(const std::string SongToPlay, const int start_time, const std::string FunctionToPlay)
{
    bool SongIsPlaying = PlaySong(SongToPlay);
    if (SongToPlay == "")
    {
        std::cout << "No song has been configured. The lightshow will play without audio" << std::endl;
    }
    if (SongIsPlaying || SongToPlay == "")
    {
        SongStartTime = std::chrono::high_resolution_clock::now() - std::chrono::seconds(start_time);
        WaitTimeTotalInMilli = 0;
        groupManager.OnStart();
        RunFunction(FunctionToPlay);
        StopSong();
        groupManager.OnEnd();
    }
    else
    {
        std::cout << "There was an error loading the song!" << std::endl;
    }
}

bool SongPlayer::PlaySong(const std::string SongToPlay, const int start_at)
{
    gMusic = Mix_LoadMUS(SongToPlay.c_str());

    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    else
    {
        Mix_PlayMusic(gMusic, 1); //Play the music once
        Mix_SetMusicPosition(start_at);
        return true;
    }
}
void SongPlayer::StopSong()
{
    if (Mix_PlayingMusic() != 0)
    {
        Mix_FreeMusic(gMusic);
        gMusic = NULL;
        Mix_Quit();
    }
}

void SongPlayer::On_Tick()
{
    groupManager.On_Tick();
}
