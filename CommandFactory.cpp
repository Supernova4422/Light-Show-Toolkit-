#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandFactory.h"
#include <iostream>
using namespace std;

std::map <string, string> Dictionary;



std::map<std::string, std::vector<Command>> CommandFactory::CreateFunctionHolder (std::map<std::string, std::vector<std::string>> IntermediateFile) {
    
    std::map<std::string, std::vector<Command>> FunctionsToPlay;

    for (std::map<string, vector<std::string>>::iterator it = IntermediateFile.begin(); it != IntermediateFile.end(); ++it) {
            vector<string> CleanedCommands = CleanupCommands(it->second); //TODO do this at a more appropriate time
            
            vector<Command> Commands;
            
            for (string Entry : CleanedCommands) {
                
                Commands.push_back(ParseCommand(Entry));
            }        

            FunctionsToPlay.insert(std::pair<std::string, vector<Command>>(RemoveTrailingWhiteSpace(it->first),Commands));
        }
    return FunctionsToPlay;
}

Command CommandFactory::ParseCommand(string CommandInput) {
        pair <CommandType,string> ReturningObject;
        string GroupIdentifier = "Group";
        string value = "";
        CommandType CurrentCommandType;
        CommandOperation CurrentOperation = CommandOperation::set;
        int TimesToExecute = 1;
        
        if (CommandInput[0] == '+') {
            CurrentOperation = CommandOperation::add;
            CommandInput = CommandInput.erase(0,1);
        } 
        if (CommandInput[0] == '-') {
            CurrentOperation = CommandOperation::Remove;
            CommandInput = CommandInput.erase(0,1);
        } 
        
        Dictionary.insert(std::pair<string, string>("RED","#FF0000")); //Just an example for now
        std::map <string, string>::iterator it;
        it = Dictionary.find(CommandInput);
        
        if (it != Dictionary.end()) {
            CommandInput = it->second;
        }

        if (CommandInput[0] == '#') { 
            value = CommandInput.erase(0,1); 
            CurrentCommandType = CommandType::ColourChange; 
        } else if (CommandInput.compare(0,GroupIdentifier.size(),GroupIdentifier) == 0) {
            value = CommandInput.erase(0,GroupIdentifier.size());
            CurrentCommandType = CommandType::Group;
        } else if (isdigit(CommandInput[0])) {
            bool ParsedAmountOfTimesToExecute = false;
            value = ""; 
            for (char c : CommandInput) {
                if (ParsedAmountOfTimesToExecute){
                    value += c;
                } else if (isalpha(c)) {
                    TimesToExecute = stoi(value);
                    value = c;
                    ParsedAmountOfTimesToExecute = true;
                } else  {
                    value += c;
                }
            } 
            if (ParsedAmountOfTimesToExecute) {
                CurrentCommandType = CommandType::FunctionName;
            }
            else {
                CurrentCommandType = CommandType::Wait;
            }
        } else {
            value = CommandInput;
            CurrentCommandType = CommandType::FunctionName;
        }
        return Command(CurrentCommandType,value,CurrentOperation, TimesToExecute);
}

vector<string> CommandFactory::CleanupCommands(const vector<string>& StringVector)  {
        vector<string> CommandsOnLine;
        
        for(const string& Entry : StringVector) {
            
            string CleanedCommand;
            CleanedCommand = RemoveTrailingWhiteSpace(Entry);
            
            CommandsOnLine.push_back(CleanedCommand);
        }
        return CommandsOnLine;
}

string CommandFactory::RemoveTrailingWhiteSpace(const string& StringToFix)  {
    vector<string> CommandsOnLine;
        
    bool SplittingStart = true;
            
    string StringWithoutTrailing;
    string TempString;
    char WhiteSpace = ' ';
        
        for(const char c : StringToFix) {
            if (IsWhiteSpace(c) && SplittingStart) {
                    //Do Nothing
            }
            else if (IsWhiteSpace(c)) {
                TempString = TempString + c; //Not added until a non-whitespace character is read, which prevents end of line trailing
            } else {
                StringWithoutTrailing = StringWithoutTrailing + TempString + c;
                TempString = ""; 
                SplittingStart = false;
            }
        }
    
    return StringWithoutTrailing;
}

bool CommandFactory::IsWhiteSpace(char c) {
    if (c == ' ') {
        return true;
    } else if (c == '\t') {
        return true;
    }
    else {
        return false;
    }

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

