#ifndef SONGPLAYER
#define SONGPLAYER
#include "Command.h"
#include "ProgrammableLight.h"
#include "FileParser.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
#include <ratio>
#include "GroupManager.h"
#include "config.h"

#if AUDIO_OUT == 1
#include "SDL_AudioPlayer.h"
typedef SDL_AudioPlayer AudioPlayer;
#else
#include "AudioPlayer_Dummy.h"
typedef AudioPlayer_Dummy AudioPlayer;
#endif

class SongPlayer
{
public:
    SongPlayer() : groupManager()
    {
        audioPlayer = AudioPlayer();
    }

    void RunCommand(const Command item);
    void WaitMilliseconds(const int milliseconds);
    void AddFunctionToSupportFile(const std::string, const std::vector<Command>);
    void AddParsedFileToSupportFile(std::map<std::string, std::vector<Command>> ParsedFile);
    void StartPlaying(const std::string FunctionToPlay = "Play");

    bool PlaySong();
    void PrepareSong(const std::string song_filename);
    void SetSongStart(const unsigned int start_at = 0);
    void StopSong();

    void On_Tick();

    void LoadMainFile(const std::string FileName);
    void AddSupportFile(const std::string FileName);
#if SDL_WINDOW_ENABLED == 1
    void add_sdl();
#endif
    void SetTime(unsigned int hours, unsigned int minutes);

private:
    void RunFunction(const std::string FunctionToPlay, const CommandOperation::CommandOperation Operation = CommandOperation::set);
    std::map<std::string, std::vector<Command>> SupportFile;
    std::map<std::string, std::vector<Command>> MainFile;
    std::string songFilename;
    unsigned int songStartAt = 0;
    FileParser Parser;
    GroupManager groupManager;
    std::chrono::system_clock::time_point SongStartTime;
    unsigned int WaitTimeTotalInMilli;
    AudioPlayer audioPlayer;
};
#endif