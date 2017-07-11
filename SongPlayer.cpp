#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
#include "ColourListiner.h"
#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include <chrono>
#include <thread>
#include "ConsoleLight.h"


GroupManager Manager;

 SongPlayer::SongPlayer () {
    ConsoleLight ConsoleView(Manager);
    ListeningLights.push_back(&Manager);
    
    ListeningLights.push_back(&ConsoleView);
    
}

void SongPlayer::RunFunction(std::string FunctionToPlay) {
    
    auto search = ParsedFile.find(FunctionToPlay);
    if(search != ParsedFile.end()) {
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

        if (item.type == CommandType::Group) {
            Manager.SetGroups(atoi(item.value.c_str()), item.Operation);
        } 
        
        for (ColourListiner* light : ListeningLights) {
        switch (item.type) {
            case Group:
                //light->OnCurrentGroupsUpdate();
            break;
            case ColourChange:
                if (item.Operation == add) {
                    light->AddColour(Newcolour);
                }
                if (item.Operation == Remove) {
                    light->RemoveColour(Newcolour);
                }
                if (item.Operation == set) {
                    light->SetColour(Newcolour);
                }
                
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
