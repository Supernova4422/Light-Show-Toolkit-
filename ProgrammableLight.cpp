#include "ProgrammableLight.h"
#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include <iostream>

void ProgrammableLight::SetGroup(std::vector<int> Groups, CommandOperation Operation)
{
    int group = Groups[0];
    Colour empty;
    std::pair<std::map<int,Colour>::iterator,bool> ret;

    const int* Pointer;
    switch (Operation) {
        case set :
        break;
        case add :
            for (int group : Groups) {

                ret = AllGroups.insert(std::pair<int,Colour>(group, empty));
                
                Pointer = &( (*(ret.first)).first);
                CurrentlySelectedGroups.push_back(Pointer);

                std::cout << Pointer << std::endl;
                std::cout << &*ret.first << std::endl;
            }
             //}
        break; 
        case Remove :
            //for (int group : Groups) {
            // } 
        break;
        default :
        break;
    }
    
}

