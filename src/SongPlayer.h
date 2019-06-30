#ifndef SONGPLAYER
#define SONGPLAYER
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "FileParser.h"
#include "SDL_mixer.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
#include "GroupManager.h"
class SongPlayer
{
public:
    SongPlayer() : groupManager()
    {
        //Initialize SDL for audio playback
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        }
        //Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }
    }

    void RunCommand(const Command item);
    void WaitMilliseconds(const int milliseconds);
    void AddFunctionToSupportFile(const std::string, const std::vector<Command>);
    void AddParsedFileToSupportFile(std::map<std::string, std::vector<Command>> ParsedFile);
    void StartPlaying(const std::string SongToPlay, const int start_time_in_seconds = 0, const std::string FunctionToPlay = "Play");

    bool PlaySong(const std::string SongToPlay, const int start_at = 0);
    void StopSong();

    void On_Tick();
    void LoadMainFile(const std::string FileName);
    void AddSupportFile(const std::string FileName);
    void add_sdl();

private:
    void RunFunction(const std::string FunctionToPlay, const CommandOperation Operation = CommandOperation::set);

    std::map<std::string, std::vector<Command>> SupportFile;
    std::map<std::string, std::vector<Command>> MainFile;

    FileParser Parser;
    GroupManager groupManager;
    std::chrono::high_resolution_clock::time_point SongStartTime;
    unsigned int WaitTimeTotalInMilli;
    Mix_Music *gMusic = NULL;
};
#endif