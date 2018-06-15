cmake_minimum_required(VERSION 3.7)
project(LightShowProject)

find_path(SDL2_INCLUDE_DIR NAME SDL.h HINTS "../library/SDL2/include")
find_library(SDL2_LIBRARY NAME SDL2 HINTS "../library/SDL2/lib/x86")

find_path(SDL2_NET_INCLUDE_DIR NAME SDL_net.h HINTS "../library/SDL2_net/include")
find_library(SDL2_net NAME SDL2_net HINTS "../library/SDL2_net/lib/x86/")


find_path(SDL2_MIXER_INCLUDE_DIR NAME SDL_mixer.h HINTS "../library/SDL2_mixer/include")
find_library(SDL2_mixer NAME SDL2_mixer HINTS "../library/SDL2_mixer/lib/x86/")

find_path(pigpio NAME pigpio.h HINTS "../library/pigpio")
find_library(pigpio_lib NAME pigpio_lib HINTS "../library/PThread/lib/x86/")

find_path(PThread_Include NAME pthread.h HINTS "../library/PThread/include/")
find_library(PThread NAME pthreadVC2 HINTS "../library/PThread/lib/x86/")

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
SongPlayer.cpp
BinaryLight.h
BinaryLight.cpp
GPIO_PI.h
GPIO_PI.cpp
)

add_definitions("-DHAVE_STRUCT_TIMESPEC")
SET(GCC_COVERAGE_COMPILE_FLAGS "-DHAVE_STRUCT_TIMESPEC")
target_include_directories (LightShowProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (LightShowProject PUBLIC ${WiringPi_IncludeDir})

include_directories(LightShowProject ${PThread_Include})
target_link_libraries(LightShowProject ${PThread}) 

find_library(pigpio_lib wiringPi)
include_directories(LightShowProject ${pigpio})

include_directories(LightShowProject ${SDL2_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_LIBRARY})    

include_directories(LightShowProject ${SDL2_NET_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_net})    

include_directories(LightShowProject ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(LightShowProject ${SDL2_mixer})    
