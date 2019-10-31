#pragma once
#include "string"
const std::string GROUP_IDENTIFIER = "Group";
#define STRICT_GRAMMAR 1;

/*
 * Should Milight commands be sent over wifi?
*/
#ifndef MILIGHT_ENABLED
#define MILIGHT_ENABLED 1
#endif
/*
 * Which library to use for audio playback
 * 1 - SDL
 * Else - A dummy class
*/
#ifndef AUDIO_OUT
#define AUDIO_OUT 1
#endif

/*
 * Should it be possible to use SDL to make a preview window
*/
#ifndef SDL_WINDOW_ENABLED
#define SDL_WINDOW_ENABLED 1
#endif

#define USING_SDL (AUDIO_OUT == 1 || SDL_WINDOW_ENABLED == 1 || MILIGHT_ENABLED == 1)
