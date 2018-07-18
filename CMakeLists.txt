cmake_minimum_required(VERSION 3.7)
project(LightShowProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

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
message(${OpenMilight})




add_executable(LightShowProject
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
RF24_Sender.h
ProgrammableLight.h

main.cpp
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

if(NOT IS_DIRECTORY ${OpenMilight})
	message("OpenMilight was not found. OpenMilight can be downloaded at: https://github.com/henryk/openmili however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${OpenMilight})
	message("OpenMilight has been found")
	INCLUDE_DIRECTORIES(LightShowProject ${OpenMilight} ) 
	target_sources(LightShowProject PUBLIC ${OpenMilight}/PL1167_nRF24.cpp ${OpenMilight}/MiLightRadio.cpp )
endif(NOT IS_DIRECTORY ${OpenMilight})

if(NOT IS_DIRECTORY ${RF24})
	message("RF24 was not found. RF24 can be downloaded at: https://github.com/nRF24/RF24 however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${RF24})
	message("RF24 has been found")
	INCLUDE_DIRECTORIES(LightShowProject ${RF24}) 
	target_sources(LightShowProject PUBLIC RF24_Sender.cpp)
	link_directories("/usr/local/lib/")
	target_link_libraries(LightShowProject "rf24-bcm")
endif(NOT IS_DIRECTORY ${RF24})

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




target_link_libraries(LightShowProject ${SDL2_LIBRARIES} ${SDL_NET_LIBRARIES} ${SDL_MIXER_LIBRARIES})
target_include_directories (LightShowProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



