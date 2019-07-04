#pragma once
#if AUDIO_OUT == 1
#include "SDL_mixer.h"
#include "SDL.h"

class SDL_AudioPlayer
{
public:
	SDL_AudioPlayer()
	{
		//Initialize SDL for audio playback
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		}
		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}

	bool playSong(std::string filename, unsigned int songStartAt)
	{
		gMusic = Mix_LoadMUS(filename.c_str());

		if (gMusic == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
		else
		{
			Mix_PlayMusic(gMusic, 1); //Play the music once
			Mix_SetMusicPosition(songStartAt);

			return true;
		}
	}

	void stopSong()
	{
		if (Mix_PlayingMusic() != 0)
		{
			Mix_FreeMusic(gMusic);
			gMusic = NULL;
			Mix_Quit();
		}
	}

private:
	Mix_Music *gMusic = NULL;
};
#endif