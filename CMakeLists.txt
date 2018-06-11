cmake_minimum_required(VERSION 3.7)
project(LightShowProject)

find_path(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

find_path(SDL2_NET_INCLUDE_DIR NAME SDL_net.h HINTS SDL2_net)
find_library(SDL2_net NAME SDL2_net)


find_path(SDL2_MIXER_INCLUDE_DIR NAME SDL_mixer.h HINTS SDL2_mixer)
find_library(SDL2_mixer NAME SDL2_mixer)


add_executable(LightShowProject
main.cpp
Colour.cpp
CommandDataTypes.cpp
CommandFactory.cpp
CommandLineInterface.cpp
ConsoleLight.cpp
FileParserHandler.cpp
GroupManager.cpp
LightShowFileReader.cpp
Milight.cpp
SDL_TCPSender.cpp
SDL_UDPSender.cpp
SongPlayer.cpp)

target_include_directories (LightShowProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(LightShowProject ${SDL2_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_LIBRARY})    

include_directories(LightShowProject ${SDL2_NET_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_net})    

include_directories(LightShowProject ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_mixer})    
