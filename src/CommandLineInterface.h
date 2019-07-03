
#include <string>
#include <iostream>
#include "SongPlayer.h"
#include <memory>
#include "UserCommand.h"
#include "SDL_AudioPlayer.h"
class CommandLineInterface
{
public:
    CommandLineInterface();
    void Run();
    void ParseLine(std::string Line);

private:
    std::unique_ptr<SongPlayer> Player;
    int delay = 0;

    std::vector<UserCommand> userCommands;
};