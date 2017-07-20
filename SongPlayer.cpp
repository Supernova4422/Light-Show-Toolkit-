
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
#include "ColourListiner.h"
#include "ConsoleLight.h"
#include "Milight.h"
#include <string>
#include <vector> 
#include <iostream>
#include <utility> 
#include <map>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <chrono>

GroupManager Manager;


std::map <std::string, std::vector<Command>> Dictionary;

SongPlayer::SongPlayer () {
    
}

void SongPlayer::LoadMainFile(std::string FileName) {
    MainFile = Parser.ParseFile(FileName);
}
void SongPlayer::AddSupportFile(std::string FileName) {
    AddParsedFileToSupportFile(Parser.ParseFile(FileName));
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
        

        WaitMilliseconds( (int) (timetowait * 1000) ) ;
    } 
    else {

        if (item.type == CommandType::SpecificCommand) {
            std::cout << "SPECIFIC COMMAND NOT IMPLEMENTED IN MANAGER";
            /*
            for (ProgrammableLight* Listiner : GroupChangeEventListiners) {
                Listiner->SpecificCommand(item);
            }
            */
        }

        if (item.type == CommandType::Group) {
            Manager.SetGroups(atoi(item.value.c_str()), item);
            
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
            if (item.Operation == add) {
                Manager.AddColour(Newcolour, item);
            }
            if (item.Operation == Remove) {
                Manager.RemoveColour(Newcolour, item);
            }
            if (item.Operation == set) {
                Manager.SetColour(Newcolour , item);
            }
        }
    }
}
std::chrono::high_resolution_clock::time_point SongStartTime;
int WaitTimeTotalInMilli;

void SongPlayer::WaitMilliseconds (int milliseconds) {
    
    std::cout << "Starting Wait" << milliseconds << std::endl; 
    WaitTimeTotalInMilli = WaitTimeTotalInMilli + milliseconds;
    
    while (std::chrono::high_resolution_clock::now() < (SongStartTime + std::chrono::milliseconds((int)WaitTimeTotalInMilli) ) ) { 
        //Do nothing
    }
  
    std::cout << "END WAIT" << std::endl;
}

void SongPlayer::StartPlaying(std::string FunctionToPlay , std::string SongToPlay) {
    PlaySong(SongToPlay);
    SongStartTime = std::chrono::high_resolution_clock::now();
    WaitTimeTotalInMilli = 0;
    RunFunction(FunctionToPlay);
}

void SongPlayer::PlaySong(std::string SongToPlay) {
}
