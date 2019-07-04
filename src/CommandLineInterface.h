
#include <string>
#include <iostream>
#include "SongPlayer.h"
#include <memory>
#include "UserCommand.h"
class CommandLineInterface
{
public:
    static bool RUNNING;
    CommandLineInterface();
    void Run();
    void ParseLine(std::string Line);

private:
    std::unique_ptr<SongPlayer> Player;
    std::vector<UserCommand> userCommands;
};