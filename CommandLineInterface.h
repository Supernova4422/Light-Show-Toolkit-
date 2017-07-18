
#include <string>
#include <iostream>
#include "SongPlayer.h"

class CommandLineInterface
{
    public: 
        CommandLineInterface(SongPlayer& Player);
        void ParseLine (std::string Line);
    private: 
        SongPlayer* Player;
};