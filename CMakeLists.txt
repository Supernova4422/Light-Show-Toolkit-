cmake_minimum_required(VERSION 3.7)
project(LightShowProject)

find_path(SDL2_INCLUDE_DIR NAME SDL.h HINTS "../library/SDL2/include")
find_library(SDL2_LIBRARY NAME SDL2 HINTS "../library/SDL2/lib/x86")

find_path(SDL2_NET_INCLUDE_DIR NAME SDL_net.h HINTS "../library/SDL2_net/include")
find_library(SDL2_net NAME SDL2_net HINTS "../library/SDL2_net/lib/x86/")


find_path(SDL2_MIXER_INCLUDE_DIR NAME SDL_mixer.h HINTS "../library/SDL2_mixer/include")
find_library(SDL2_mixer NAME SDL2_mixer HINTS "../library/SDL2_mixer/lib/x86/")

add_executable(LightShowProject
main.h
Colour.h
CommandDataTypes.h
CommandFactory.h
CommandLineInterface.h
ConsoleLight.h
FileParserHandler.h
GroupManager.h
LightShowFileReader.h
Milight.h
SDL_TCPSender.h
SDL_UDPSender.h
SongPlayer.h

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
SongPlayer.cpp
BinaryLight.cpp
GPIO_PI.cpp
BinLight_SYSFS.cpp
)

target_include_directories (LightShowProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(LightShowProject ${SDL2_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_LIBRARY})    

include_directories(LightShowProject ${SDL2_NET_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_net})    

include_directories(LightShowProject ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_mixer})    
