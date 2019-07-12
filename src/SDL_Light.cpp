#include "SDL_Light.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ProxyMaker.h"

SDL_Window *SDL_Light::MainWindow = nullptr;
SDL_Renderer *SDL_Light::renderer = nullptr;

void Destroy_SDL()
{
	SDL_DestroyWindow(SDL_Light::MainWindow);
}
SDL_Light::SDL_Light()
{
	atexit(SDL_Quit);
	atexit(Destroy_SDL);
	proxies = ProxyMaker::proxy_filereader("groups/SDL_LIGHT_PROXY.txt");
	ProxyMaker::print_proxies(proxies);
	if (renderer == nullptr)
	{
		std::cout << "Loading window" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "error 0" << std::endl;
		}
		else
		{
			SDL_Light::MainWindow = SDL_CreateWindow(
				"Lightshow Toolkit",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				640,
				480,
				0);

			if (SDL_Light::MainWindow == NULL)
			{
				std::cout << "error 1" << std::endl;
			}
			else
			{
				renderer = SDL_CreateRenderer(SDL_Light::MainWindow, -1, 0);
				if (SDL_Light::renderer == nullptr)
				{
					std::cout << "error 2" << std::endl;
				}
				else
				{
					std::cout << "Initialised SDL Light, the window can be closed when the song is running, or when the application exits." << std::endl;
					SDL_SetRenderDrawColor(SDL_Light::renderer, 255, 255, 0, 255);
					SDL_RenderPresent(SDL_Light::renderer);
					SDL_ShowWindow(SDL_Light::MainWindow);
					On_Tick();
				}
			}
		}
	}
}

void SDL_Light::On_Tick()
{
}

void SDL_Light::EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput)
{

	for (auto it : ExpectedOutput)
	{
		groups[it.first] = it.second;
	}

	int size = 0;
	for (auto it = groups.begin(); it != groups.end(); it++)
	{
		size++;
	}

	if (size > 0)
	{
		const int divisions = (640 / size);
		const int width = divisions * 0.9f;
		const int gap = divisions * 0.1f;
		std::cout << width << std::endl;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		int i = 0;
		for (auto it = groups.begin(); it != groups.end(); it++)
		{
			SDL_SetRenderDrawColor(renderer, it->second.get_colour().red, it->second.get_colour().green, it->second.get_colour().blue, 255);
			SDL_Rect light_rect = {divisions * (i) + gap, 0, divisions - gap, 480};
			SDL_RenderFillRect(renderer, &light_rect);
			i++;
		}
		SDL_RenderPresent(renderer);
	}
	//On_Tick can only be from the main thread!
	//On_Tick();
}
