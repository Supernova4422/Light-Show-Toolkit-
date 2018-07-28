cmake_minimum_required(VERSION 3.7)
project(LightShowProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x -DRPI -lwiringPi")
set(CMAKE_BUILD_TYPE Debug)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2  sdl2)
PKG_SEARCH_MODULE(SDL_NET  SDL2_net>=2.0.0)
PKG_SEARCH_MODULE(SDL_MIXER  SDL2_mixer>=2.0.0)

find_path(SDL2_INCLUDE_DIRS NAME SDL.h HINTS "../library/SDL2/include")
find_library(SDL2_LIBRARIES NAME SDL2 HINTS "../library/SDL2/lib/x86")

find_path(SDL_NET_INCLUDE_DIRS NAME SDL_net.h HINTS "../library/SDL2_net/include")
find_library(SDL_NET_LIBRARIES NAME SDL2_net HINTS "../library/SDL2_net/lib/x86/")


find_path(SDL_MIXER_INCLUDE_DIRS NAME SDL_mixer.h HINTS "../library/SDL2_mixer/include")
find_library(SDL_MIXER_LIBRARIES NAME SDL2_mixer HINTS "../library/SDL2_mixer/lib/x86/")

find_path(OpenMilight NAME MiLightRadio.h)
find_path(RF24 NAME RF24.h)
find_path(V6_Encoding NAME V2RFEncoding.h)
find_path(RC-Switch NAME RCSwitch.h)

message(${OpenMilight})

add_executable(LightShowProject
BinaryLightController.h
Colour.h
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
BinaryLight.h
GPIO_PI.h
BinLight_SYSFS.h
ProgrammableLight.h

main.cpp
BinaryLightController.cpp
Colour.cpp
Color_Combiner.cpp
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

INCLUDE_DIRECTORIES(LightShowProject ${SDL2_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS} ${SDL_NET_INCLUDE_DIRS}) 

if(${SDL2_FOUND})
	message("SDL2 FOUND" )
elseif()
	message(status "SDL2 NOT FOUND")
endif(${SDL2_FOUND})

if(${SDL_NET_FOUND})
	message("SDL2_NET FOUND")
elseif()
	message(status "SDL2_NET NOT FOUND")
endif(${SDL_NET_FOUND})

if(${SDL_MIXER_FOUND})
	message("SDL2_MIXER FOUND")
elseif()
	message(status "SDL2_MIXER NOT FOUND")
endif(${SDL_MIXER_FOUND})

if(NOT IS_DIRECTORY ${RC-Switch})
	message("RC-Switch was not found. RC-Switch can be downloaded at: https://github.com/sui77/rc-switch however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${RC-Switch})
	target_link_libraries(LightShowProject 433)
endif(NOT IS_DIRECTORY ${RC-Switch})

if(NOT IS_DIRECTORY ${RF24})
	message("RF24 was not found. RC-Switch can be downloaded at: https://github.com/sui77/rc-switch however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${RF24})
	target_link_libraries(LightShowProject RF24_proj)
endif(NOT IS_DIRECTORY ${RF24})

target_link_libraries(LightShowProject ${SDL2_LIBRARIES} ${SDL_NET_LIBRARIES} ${SDL_MIXER_LIBRARIES})
target_include_directories (LightShowProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



