#ifndef SDL_LIGHT_H
#define SDL_LIGHT_H
#include "SDL.h"
#include "ProgrammableLight.h"
#include "ProxyMaker.h"
class SDL_Light : public ProgrammableLight, public Tick_Listener
{
    public: 
    SDL_Light();
    void SetColourForCurrentGroups(const colour_combiner OutputColour){};
    void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput);
    void SpecificCommand(const Command command){};
    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, colour_combiner>*>  CurrentGroups){};
    void On_Tick();
private: 
	std::map<std::set<int>, int, cmpBySetSize> proxies;
    std::map<int, colour_combiner> groups;
    bool started = false;
    SDL_Renderer* renderer = NULL;
    SDL_Window* MainWindow = NULL;
};

#endif // SDL_LIGHT_H