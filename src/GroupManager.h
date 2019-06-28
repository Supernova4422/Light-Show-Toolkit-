#ifndef GROUPMANAGER_01
#define GROUPMANAGER_01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "ProgrammableLight.h"
#include "Color_Combiner.cpp"
#include "Tick_Listener.h"
#include <set>
class GroupManager : public Tick_Listener
{
public:
  GroupManager(){};
  void SetGroups(const int Group, const Command CommandItem);
  void AddToCurrentGroups(const int GroupToAdd);
  void UpdateColour(const Colour OutputColour, const Command item);
  void SpecificCommand(const Command command);
  void On_Tick();

  template <class T>
  void AddTickListener()
  {
    TickListeners.push_back(std::make_unique<T>());
  }

  template <class T, class... _Args>
  void AddLight(_Args &&... __args)
  {
    ListeningLights.push_back(std::make_unique<T>(std::forward<_Args>(__args)...));
  }

private:
  std::map<int, colour_combiner> AllGroups;
  std::set<int> CurrentlySelectedGroups;
  colour_combiner CurrentSelectedColour;

  std::vector<std::unique_ptr<ProgrammableLight>> ListeningLights;
  std::vector<std::unique_ptr<Tick_Listener>> TickListeners;
};
#endif