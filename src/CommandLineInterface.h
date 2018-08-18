
#include <string>
#include <iostream>
#include "SongPlayer.h"

class CommandLineInterface
{
    public: 
        CommandLineInterface(SongPlayer* Player);
        
		void Run();
    private: 
        SongPlayer* Player;
		void ParseLine(std::string Line);
};