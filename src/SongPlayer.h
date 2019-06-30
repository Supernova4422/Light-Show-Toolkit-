#ifndef SONGPLAYER
#define SONGPLAYER
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "FileParserHandler.h"
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
    SongPlayer();

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
    std::map<std::string, std::vector<Command>> SupportFile;
    void RunFunction(const std::string FunctionToPlay, const CommandOperation Operation = CommandOperation::set);
    std::unique_ptr<GroupManager> manager;
    std::map<std::string, std::vector<Command>> MainFile;
    std::vector<std::unique_ptr<ProgrammableLight>> GroupChangeEventListiners;
    FileParserHandler Parser;
    std::chrono::high_resolution_clock::time_point SongStartTime;
    int WaitTimeTotalInMilli;

    //The music that will be played
    Mix_Music *gMusic = NULL;
};
#endif