#ifndef CommandFactoryDef
#define CommandFactoryDef

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"

class CommandFactory
{
public:
    std::map<std::string, std::vector<Command>> CreateFunctionHolder(std::map<std::string, std::vector<std::string>> IntermediateFile) const;

    Command ParseCommand(const std::string CommandInput) const;

private:
    std::vector<std::string> CleanupCommands(const std::vector<std::string> &StringVector) const;
    std::string RemoveTrailingWhiteSpace(const std::string &StringToFix) const;
    bool IsWhiteSpace(const char c) const;
};
#endif