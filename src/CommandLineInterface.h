
#include <string>
#include <iostream>
#include "SongPlayer.h"
#include <memory>
class CommandLineInterface
{
public:
    CommandLineInterface();

    void Run();

private:
    std::unique_ptr<SongPlayer> Player;
    int delay = 0;
    void ParseLine(std::string Line);
};