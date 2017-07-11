#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
class SongPlayer
{
    public: 
    void RunCommand(Command item);
    void RunFunction(std::string FunctionToPlay);
    void WaitMilliseconds(float milliseconds);
    SongPlayer();
    std::vector<ColourListiner*> ListeningLights;
    std::map<std::string, std::vector<Command>> ParsedFile;
    std::vector<ProgrammableLight*> GroupChangeEventListiners;
};