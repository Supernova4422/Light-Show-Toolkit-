#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include <chrono>
#include <thread>

void SongPlayer::RunFunction(std::string FunctionToPlay) {
    
    auto search = ParsedFile.find(FunctionToPlay);
    if(search != ParsedFile.end()) {
        std::cout << "Found " << search->first << '\n';
        for (Command item : search->second) {
            RunCommand(item);
        }
    }
} 
void SongPlayer::RunCommand(Command item) {
    Colour Newcolour(item.value);
    //Make into seperate function to make recursive
    if (item.type == CommandType::Wait) {
        int timetowait = std::stoi(item.value.c_str(), nullptr , 10) * 10;
        std::cout << "WAIT: " << timetowait << '\n';
        //TODO IMPLEMENT A WAIT FUNCTION


        //std::this_thread::sleep_for(std::chrono::seconds(1));
    } 
    else {
        for (ProgrammableLight* light : ListeningLights) {
        switch (item.type) {
            case Group:
                light->SetGroups(atoi(item.value.c_str()), item.Operation);
            break;
            case ColourChange:
                light->EmitColour(Newcolour);
            break;
            
            case FunctionName:
                RunFunction(item.value);
            break;
            
            case FunctionPointer:
                //TODO runfunction via reference
            break;
            }
        }
    }
}
