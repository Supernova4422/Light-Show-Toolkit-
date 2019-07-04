#include "SDL_Light.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ProxyMaker.h"

SDL_Light::SDL_Light()
{
	proxies = ProxyMaker::proxy_filereader("proxy.txt");
	ProxyMaker::print_proxies(proxies);
	if (renderer == NULL)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "error 0" << std::endl;
		}
		else
		{
			MainWindow = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
			if (MainWindow == NULL)
			{
				std::cout << "error 1" << std::endl;
			}
			else
			{
				renderer = SDL_CreateRenderer(MainWindow, -1, 0);
				if (renderer == NULL)
				{
					std::cout << "error 2" << std::endl;
				}
				else
				{
					std::cout << "Initialised SDL Light" << std::endl;
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
}

void SDL_Light::On_Tick()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			SDL_DestroyWindow(MainWindow);
		}
	}
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
	On_Tick();
}
