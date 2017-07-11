
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
#include <ctime>
#include <iomanip>
GroupManager Manager;
ConsoleLight ConsoleView(Manager);
 SongPlayer::SongPlayer () {
    
    GroupChangeEventListiners.push_back(&ConsoleView);

    ListeningLights.push_back(&Manager);

    ListeningLights.push_back(&ConsoleView);
    
}

void SongPlayer::RunFunction(std::string FunctionToPlay) {
    
    auto search = ParsedFile.find(FunctionToPlay);
    if(search != ParsedFile.end()) {
        for (Command item : search->second) {
            for (int i = 0; i < item.TimesToExecute; i++) {
                RunCommand(item);
            }
            
        }
    }
} 
void SongPlayer::RunCommand(Command item) {
    Colour Newcolour(item.value);
    
    
    //Make into seperate function to make recursive
    if (item.type == CommandType::Wait) {
        float timetowait = std::atof(item.value.c_str());
        std::cout << std::setprecision(5);
        std::cout << "WAIT: " << timetowait << '\n';
        //TODO IMPLEMENT A WAIT FUNCTION

        WaitMilliseconds(timetowait * 1000);
    } 
    else {

        if (item.type == CommandType::Group) {
            Manager.SetGroups(atoi(item.value.c_str()), item.Operation);
            for (ProgrammableLight* Listiner : GroupChangeEventListiners) {
                Listiner->OnCurrentGroupsUpdate(Manager);
            }
        } 

        
        for (ColourListiner* light : ListeningLights) {
        switch (item.type) {
            
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

void SongPlayer::WaitMilliseconds (float milliseconds) {

    clock_t EndTime;
    EndTime = clock() + (milliseconds);
    while (clock() < EndTime) { 
        //Do nothing
    }
}