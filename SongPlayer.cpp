
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "SongPlayer.h"
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
#include <fstream>
#include <SDL.h>
#include <SDL_mixer.h>

GroupManager Manager;


std::map <std::string, std::vector<Command>> Dictionary;

SongPlayer::SongPlayer () {
    //Initialize SDL for audio playback
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
     //Initialize SDL_mixer
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }            
    
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
        
        WaitMilliseconds( (int) (timetowait * 1000) ) ;
    } 
    else {

        if (item.type == CommandType::SpecificCommand) {
            Manager.SpecificCommand(item);
        }

        if (item.type == CommandType::Group) {
            Manager.SetGroups(atoi(item.value.c_str()), item);
            
        } 
        if (item.type == CommandType::FunctionName){
            for (int i = 0; i < item.TimesToExecute; i++) {
                    RunFunction(item.value, item.Operation);
                }
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
    
    std::cout << "Starting wait for: " << milliseconds << " Milliseconds" << std::endl; 
    WaitTimeTotalInMilli = WaitTimeTotalInMilli + milliseconds;
    
    while (std::chrono::high_resolution_clock::now() < (SongStartTime + std::chrono::milliseconds((int)WaitTimeTotalInMilli) ) ) { 
        //Do nothing
    }
  
    std::cout << "Finished Waiting" << std::endl;
}

void SongPlayer::StartPlaying(std::string SongToPlay , std::string FunctionToPlay ) {
    bool SongIsPlaying;
    SongIsPlaying = PlaySong(SongToPlay);

    if (SongIsPlaying) {
        SongStartTime = std::chrono::high_resolution_clock::now();
        WaitTimeTotalInMilli = 0;
        RunFunction(FunctionToPlay);
        StopSong();
    } else {
        std::cout << "There was an error loading the song!" << std::endl;
    }
}

bool loadMedia()
{

}
//The music that will be played
Mix_Music *gMusic = NULL;

bool SongPlayer::PlaySong(std::string SongToPlay) {
    
    bool success = true;
    gMusic = Mix_LoadMUS( SongToPlay.c_str() );
    
    if( gMusic == NULL ) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    } else {
        Mix_PlayMusic( gMusic, 1 ); //Play the music once        
    }  
          
    return success; 
}
void SongPlayer::StopSong() {
    if( Mix_PlayingMusic() != 0 ) {
        //Free and stop the music
        Mix_FreeMusic( gMusic );
        gMusic = NULL;
        Mix_Quit(); 
    }
}