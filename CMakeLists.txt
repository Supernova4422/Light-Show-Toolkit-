cmake_minimum_required(VERSION 3.7)
project(LightShowProject_Oversight)

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

add_subdirectory(433) 
add_subdirectory(RF24_proj) 
add_subdirectory(src) 


