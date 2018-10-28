#ifndef GROUPMANAGER_01
#define GROUPMANAGER_01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "ProgrammableLight.h"
#include "Color_Combiner.cpp"
#include "Tick_Listener.h"
class GroupManager : public Tick_Listener
{
  public:
    void SetGroups(const int Group, Command CommandItem);
    void AddToCurrentGroups(const int GroupToAdd);
    void UpdateColour(const Colour OutputColour , Command item);
    void SpecificCommand(const Command command);
    
    GroupManager();

	void AddLight(ProgrammableLight* light);
	void AddTickListener(Tick_Listener* light);
	void On_Tick();
    std::pair<const int, colour_combiner> *GetGroupByID(const int ID);
    std::vector<std::pair<const int, colour_combiner>*> CurrentlySelectedGroups;
  private:
    std::map<int, colour_combiner> AllGroups;
	colour_combiner CurrentSelectedColour;
    std::vector<ProgrammableLight*> ListeningLights;
	std::vector<Tick_Listener*> TickListeners;
    
};
#endif