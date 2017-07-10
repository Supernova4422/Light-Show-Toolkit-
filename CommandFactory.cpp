#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandFactory.h"
#include <iostream>
using namespace std;

Command CommandFactory::ParseCommand(string CommandInput) {
        pair <CommandType,string> ReturningObject;
        string GroupIdentifier = "Group";
        string value = "";
        CommandType CurrentCommandType;
        CommandOperation CurrentOperation = CommandOperation::set;
        
        if (CommandInput[0] == '+') {
            CurrentOperation = CommandOperation::add;
            CommandInput = CommandInput.erase(0,1);
        } 
        if (CommandInput[0] == '-') {
            CurrentOperation = CommandOperation::Remove;
            CommandInput = CommandInput.erase(0,1);
        } 
        
        if (CommandInput[0] == '#') { 
            value = CommandInput.erase(0,1); 
            CurrentCommandType = CommandType::ColourChange; 
        } else if (CommandInput.compare(0,GroupIdentifier.size(),GroupIdentifier) == 0) {
            value = CommandInput.erase(0,GroupIdentifier.size());
            CurrentCommandType = CommandType::Group;
        } else if (isdigit(CommandInput[0])) { 
            value = CommandInput;
            CurrentCommandType = CommandType::Wait;
        } else {
            value = CommandInput;
            CurrentCommandType = CommandType::FunctionName;
        }

        return Command(CurrentCommandType,value,CurrentOperation);
    }

std::map<std::string, std::vector<Command>> CommandFactory::CreateFunctionHolder (std::map<std::string, std::vector<std::string>> IntermediateFile) {
    
    std::map<std::string, std::vector<Command>> FunctionsToPlay;

    for (std::map<string, vector<std::string>>::iterator it = IntermediateFile.begin(); it != IntermediateFile.end(); ++it) {
            vector<string> CleanedCommands = RemoveTrailingWhiteSpace(it->second); //TODO do this at a more appropriate time
            vector<Command> Commands;
            
            for (string Entry : CleanedCommands) {
                
                Commands.push_back(ParseCommand(Entry));
            }        

            FunctionsToPlay.insert(std::pair<std::string, vector<Command>>(it->first,Commands));
        }
    return FunctionsToPlay;
}

void ConvertMacrosToPointers (std::map<std::string, std::vector<Command>> *FunctionCollection) {
    /*
    for (std::map<string, vector<Command>>::iterator it = FunctionCollection->begin(); it != FunctionCollection->end(); ++it) {
                
                vector<Command> Commands;
                for (Command Entry : it->second) {
                    if (Entry.type == CommandType.FunctionName) {
                        Entry.value == &FunctionCollection->find(Entry.value)
                    }
                }        
                FunctionsToPlay.insert(std::pair<std::string, vector<Command>>(it->first,Commands));
            }
    */
}
void CommandFactory::PrintAll(std::map <string, vector<string>> FunctionsWithCommands ){
    for (std::map<string, vector<string>>::iterator it = FunctionsWithCommands.begin(); it != FunctionsWithCommands.end(); ++it) {
            cout << "Function Name:" << it->first << endl;
            for (string item : it->second) {
                cout << "Command Name:" << item << endl;
            }
    }
}

vector<string> CommandFactory::RemoveTrailingWhiteSpace(const vector<string>& StringVector)  {
        vector<string> CommandsOnLine;
        for(const string& Entry : StringVector) {
            bool SplittingStart = true;
            
            string StringWithoutTrailing;
            string TempString;
            char WhiteSpace = ' ';
            for(const char c : Entry) {
                if (c == WhiteSpace && SplittingStart) {
                    //Do Nothing
                }
                else if (c == WhiteSpace) {
                    TempString = TempString + c; //Not added until a non-whitespace character is read, which prevents end of line trailing
                } else {
                    StringWithoutTrailing = StringWithoutTrailing + TempString + c;
                    TempString = ""; 
                    SplittingStart = false;
                }
            }
            CommandsOnLine.push_back(StringWithoutTrailing);
        }
        
        return CommandsOnLine;
    }
