
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
#include "ColourListiner.h"
#include <string>
#include <vector> 
#include <iostream>
#include <utility> 
#include <map>
#include <chrono>
#include <thread>
#include "ConsoleLight.h"
#include "Milight.h"
#include <ctime>
#include <iomanip>

GroupManager Manager;
ConsoleLight ConsoleView(Manager);
Milight TestLight(Manager);


std::map <std::string, std::vector<Command>> Dictionary;

SongPlayer::SongPlayer () {
    
    GroupChangeEventListiners.push_back(&ConsoleView);
    GroupChangeEventListiners.push_back(&TestLight);
    
    ListeningLights.push_back(&Manager);
    ListeningLights.push_back(&ConsoleView);
    ListeningLights.push_back(&TestLight);

    
    
}
void SongPlayer::AddFunctionToSupportFile(std::string FunctionName, std::vector<Command> Commands) {
    SupportFile.insert(std::pair<std::string, std::vector<Command>>(FunctionName,Commands));
}
void SongPlayer::AddParsedFileToSupportFile(std::map<std::string, std::vector<Command>> ParsedFile) {
    for (std::pair<std::string, std::vector<Command>> item : ParsedFile ) {
        AddFunctionToSupportFile(item.first,item.second);
    }
}
void SongPlayer::RunFunction(std::string FunctionToPlay , CommandOperation Operation) {
    
    auto search = MainFile.find(FunctionToPlay);

    if (search == MainFile.end()) //Error, didn't find the function
    {
        search = SupportFile.find(FunctionToPlay); 
        if (search == SupportFile.end()) { //Error didn't find the function
            return; //Return to break the cycle
        }
    }

    //Due to the return statement above, this is only reachable if we find a function
    for (Command item : search->second) {
            if (Operation != CommandOperation::set) {
                Command CommandTempItem = item;
                CommandTempItem.Operation = Operation;
                RunCommand(CommandTempItem);
            } else {
                RunCommand(item);
            }
    }

  
} 
void SongPlayer::RunCommand(Command item ) {
    
    
    
    //Make into seperate function to make recursive
    if (item.type == CommandType::Wait) {
        float timetowait = std::atof(item.value.c_str());
        std::cout << std::setprecision(5);
        std::cout << "WAIT: " << timetowait << '\n';
        

        WaitMilliseconds(timetowait * 1000);
    } 
    else {

        if (item.type == CommandType::SpecificCommand) {
            for (ProgrammableLight* Listiner : GroupChangeEventListiners) {
                Listiner->SpecificCommand(item);
            }
        }

        if (item.type == CommandType::Group) {
            Manager.SetGroups(atoi(item.value.c_str()), item.Operation);
            for (ProgrammableLight* Listiner : GroupChangeEventListiners) {
                Listiner->OnCurrentGroupsUpdate(Manager);
            }
        } 
        if (item.type == CommandType::FunctionName){
            for (int i = 0; i < item.TimesToExecute; i++) {
                    RunFunction(item.value, item.Operation);
                }
        }

        if (item.type == CommandType::FunctionPointer) {

        }
        

        if (item.type == CommandType::ColourChange) {
            Colour Newcolour(item.value);
            for (ColourListiner* light : ListeningLights) {
                if (item.Operation == add) {
                    light->AddColour(Newcolour);
                }
                if (item.Operation == Remove) {
                    light->RemoveColour(Newcolour);
                }
                if (item.Operation == set) {
                    light->SetColour(Newcolour);
                }
            }
        }
    }
}

clock_t SongStartTime;
float WaitTimeTotal;

void SongPlayer::WaitMilliseconds (float milliseconds) {
    
    WaitTimeTotal = WaitTimeTotal + milliseconds;
    std::cout << "START WAIT" << std::endl;
    while (clock() < (SongStartTime + WaitTimeTotal) ) { 
        //Do nothing
    }
    std::cout << "END WAIT" << std::endl;
}

void SongPlayer::StartPlaying(std::string FunctionToPlay , std::string SongToPlay) {
    PlaySong(SongToPlay);
    SongStartTime = clock();
    RunFunction(FunctionToPlay);
}

void SongPlayer::PlaySong(std::string SongToPlay) {
}
