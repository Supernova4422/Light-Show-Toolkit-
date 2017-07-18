#ifndef CommandFactoryDef
#define CommandFactoryDef

#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
using namespace std;

class CommandFactory {
    public:
        
        std::map<std::string, std::vector<Command>> CreateFunctionHolder (std::map<std::string, std::vector<std::string>> IntermediateFile);
        Command ParseCommand(string CommandInput);

        void ConvertMacrosToPointers (std::map<std::string, std::vector<Command>> *FunctionCollection);
    private: 
        vector<string> CleanupCommands(const vector<string>& StringVector);
        string RemoveTrailingWhiteSpace(const string& StringToFix);
        bool IsWhiteSpace(char c);
        void PrintAll(std::map <string, vector<string>> FunctionsWithCommands );
};
#endif