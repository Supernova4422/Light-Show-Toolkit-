#include <string>
#include <vector>
#include <utility>
#include <map>

#include "Command.h"
#include "LightShowFileReader.h"

class FileParser
{
public:
    std::map<std::string, std::vector<Command>> ParseFile(std::string FileToParse)
    {
        std::cout << "Parsing: " << FileToParse << std::endl;
        LightShowFileReader parser = LightShowFileReader();
        std::map<std::string, std::vector<std::string>> IntermediateFile = parser.ParseFile(FileToParse);

        if (IntermediateFile.empty())
        {
            std::cout << "The file was empty!" << std::endl;
        }

        return CreateFunctionHolder(IntermediateFile);
    }

private:
    std::map<std::string, std::vector<Command>> CreateFunctionHolder(std::map<std::string, std::vector<std::string>> IntermediateFile) const
    {
        std::map<std::string, std::vector<Command>> FunctionsToPlay;

        for (auto it = IntermediateFile.begin(); it != IntermediateFile.end(); ++it)
        {
            auto CleanedCommands = CleanupCommands(it->second);

            std::vector<Command> Commands;
            for (const auto Entry : CleanedCommands)
            {
                Commands.push_back(Command(Entry));
            }

            FunctionsToPlay.insert(std::make_pair(RemoveTrailingWhiteSpace(it->first), Commands));
        }
        return FunctionsToPlay;
    }

    std::vector<std::string> CleanupCommands(const std::vector<std::string> &StringVector) const
    {
        std::vector<std::string> CommandsOnLine;

        for (const std::string &Entry : StringVector)
        {
            auto cleaned = RemoveTrailingWhiteSpace(Entry);
            if (cleaned != "")
            {
                CommandsOnLine.push_back(cleaned);
            }
        }

        return CommandsOnLine;
    }
    std::string RemoveTrailingWhiteSpace(const std::string &StringToFix) const
    {
        std::string StringWithoutTrailing = "";

        for (const char c : StringToFix)
        {
            if (IsWhiteSpace(c) == false)
            {
                StringWithoutTrailing += c;
            }
        }

        return StringWithoutTrailing;
    }

    bool IsWhiteSpace(const char c) const
    {
        if (c == ' ')
        {
            return true;
        }
        else if (c == '\t')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
