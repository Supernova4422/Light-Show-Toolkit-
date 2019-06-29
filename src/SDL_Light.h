#ifndef SDL_LIGHT_H
#define SDL_LIGHT_H
#include "SDL.h"
#include "ProgrammableLight.h"
#include "ProxyMaker.h"
#include "Tick_Listener.h"
class SDL_Light : public ProgrammableLight, public Tick_Listener
{
public:
    SDL_Light();

    void SetColourForCurrentGroups(const colour_combiner OutputColour){};

    void EmitColour(const Command CommandItem, const std::map<int, colour_combiner> ExpectedOutput) override;

    void SpecificCommand(const Command command, const std::map<int, colour_combiner> CurrentGroups) override{};

    void OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, colour_combiner> CurrentGroups) override{};

    void On_Tick() override;

    void OnStart() override {}; //TODO

    void OnEnd() override {}; //TODO

private:
    std::map<std::set<int>, int, cmpBySetSize> proxies;
    std::map<int, colour_combiner> groups;
    SDL_Renderer *renderer = NULL;
    SDL_Window *MainWindow = NULL;
};

#endif // SDL_LIGHT_H