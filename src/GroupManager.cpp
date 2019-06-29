
#include "GroupManager.h"
#include "ConsoleLight.h"
#include "Milight.h"

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

void GroupManager::On_Tick()
{
    for (auto &listener : TickListeners)
    {
        listener->On_Tick();
    }
}

void GroupManager::SetGroups(const int Group, const Command CommandItem)
{
    switch (CommandItem.Operation)
    {
    case set:
        CurrentlySelectedGroups.clear();
        CurrentlySelectedGroups.insert(Group);
        break;
    case add:
        CurrentlySelectedGroups.insert(Group);
        break;
    case Remove:
        CurrentlySelectedGroups.erase(Group);
        break;
    }

    std::map<int, colour_combiner> current_groups;
    for (auto entry : CurrentlySelectedGroups)
    {
        current_groups[entry] = AllGroups[entry];
    }

    for (auto &light : ListeningLights)
    {
        light->OnCurrentGroupsUpdate(CommandItem, current_groups);
    }

    std::cout << "Current Groups are now: ";
    for (auto group : current_groups)
    {
        std::cout << group.first << ", ";
    }
    std::cout << std::endl;
}

void GroupManager::UpdateColour(const Colour OutputColour, const Command item)
{
    for (auto group : CurrentlySelectedGroups)
    {
        AllGroups[group].set_new(OutputColour, item.Operation);
    }

    std::map<int, colour_combiner> current_groups;
    for (auto entry : CurrentlySelectedGroups)
    {
        current_groups[entry] = AllGroups[entry];
    }

    for (auto &light : ListeningLights)
    {
        light->EmitColour(item, current_groups);
    }
}

void GroupManager::SpecificCommand(const Command command)
{
    std::map<int, colour_combiner> current_groups;
    for (auto entry : CurrentlySelectedGroups)
    {
        current_groups[entry] = AllGroups[entry];
    }

    for (auto &light : ListeningLights)
    {
        light->SpecificCommand(command, current_groups);
    }
}