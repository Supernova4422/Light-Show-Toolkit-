#ifndef SONGPLAYER
#define SONGPLAYER
#include "CommandDataTypes.cpp"
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

#ifndef AUDIO_OUT
#define AUDIO_OUT = (0);
#endif

/* Which device to use for audio playback
 * 1 - SDL
 * Else - A dummy class
*/
#ifdef AUDIO_OUT==1
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
        audioPlayer = SDL_AudioPlayer();
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
    void add_sdl();

    void printTime(long total_seconds)
    {
    }

    void SetTime(unsigned int hours, unsigned int minutes, unsigned int seconds)
    {
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
        std::chrono::system_clock::duration dtn = tp.time_since_epoch();
        const auto total_seconds = dtn.count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

        const auto seconds_now = total_seconds % 60;
        const auto minutes_total = total_seconds / 60;
        const auto minutes_now = minutes_total % 60;
        const auto hours_total = minutes_total / 60;
        const auto hours_now = hours_total % 60;
        const auto days_total = hours_total / 24;

        std::cout
            << "Time is: "
            << std::to_string(days_total) << ":"
            << std::to_string(hours_now) << ":"
            << std::to_string(minutes_now) << ":"
            << std::to_string(seconds_now)
            << std::endl;

        const auto seconds_in_a_day = 60 * 60 * 24;
        const auto offset = (days_total * seconds_in_a_day) + (hours * 60 * 60) + (minutes * 60) + (seconds);
        const auto start_time = std::chrono::seconds(offset);
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tp_seconds(start_time);

        const auto run_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(tp_seconds).time_since_epoch());
        std::cout << run_seconds.count() << std::endl;
    };

private:
    void RunFunction(const std::string FunctionToPlay, const CommandOperation Operation = CommandOperation::set);

    std::map<std::string, std::vector<Command>> SupportFile;
    std::map<std::string, std::vector<Command>> MainFile;
    std::string songFilename;
    unsigned int songStartAt = 0;
    FileParser Parser;
    GroupManager groupManager;
    std::chrono::high_resolution_clock::time_point SongStartTime;
    unsigned int WaitTimeTotalInMilli;
    AudioPlayer audioPlayer;
};
#endif