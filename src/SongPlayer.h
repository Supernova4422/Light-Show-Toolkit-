#ifndef SONGPLAYER
#define SONGPLAYER
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "FileParserHandler.h"

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

    void RunCommand(Command item);
    void WaitMilliseconds(int milliseconds);
    void AddFunctionToSupportFile(std::string, std::vector<Command>);
    void AddParsedFileToSupportFile(std::map<std::string, std::vector<Command> > ParsedFile);
    void StartPlaying(std::string SongToPlay, int start_time_in_seconds = 0, std::string FunctionToPlay = "Play");

    bool PlaySong(std::string SongToPlay, int start_at = 0);
    void StopSong();

	void On_Tick();
    void LoadMainFile(std::string FileName);
    void AddSupportFile(std::string FileName);
    void add_sdl();

private:
    std::map<std::string, std::vector<Command> > SupportFile;
    void RunFunction(std::string FunctionToPlay , CommandOperation Operation = CommandOperation::set);
    std::unique_ptr<GroupManager> manager;
    std::map<std::string, std::vector<Command>> MainFile;
    std::vector<std::unique_ptr<ProgrammableLight>> GroupChangeEventListiners;
    FileParserHandler Parser;
};
#endif