#include <string>
#include <vector>
#include <utility>
#include <map>

#include "CommandDataTypes.cpp"
#include "LightShowFileReader.h"
#include "CommandFactory.h"

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
                Commands.push_back(ParseCommand(Entry));
            }

            FunctionsToPlay.insert(std::make_pair(RemoveTrailingWhiteSpace(it->first), Commands));
        }
        return FunctionsToPlay;
    }

    Command ParseCommand(std::string CommandInput) const
    {
        std::string GroupIdentifier = "Group";
        std::string value = CommandInput;
        CommandType CurrentCommandType = CommandType::FunctionName;
        CommandOperation CurrentOperation = CommandOperation::set;
        unsigned int TimesToExecute = 1;
        if (CommandInput[0] == '+')
        {
            CurrentOperation = CommandOperation::add;
            CommandInput = CommandInput.erase(0, 1);
        }
        if (CommandInput[0] == '-')
        {
            CurrentOperation = CommandOperation::Remove;
            CommandInput = CommandInput.erase(0, 1);
        }
        if (CommandInput[0] == '=')
        {
            CurrentOperation = CommandOperation::Set;
            CommandInput = CommandInput.erase(0, 1);
        }

        if ((CommandInput[0] == '[') && (CommandInput.back() == ']'))
        {
            value = CommandInput.erase(0, 1);
            value = value.substr(0, value.size() - 1);
            CurrentCommandType = CommandType::SpecificCommand;
        }
        else if (CommandInput[0] == '#')
        {
            value = CommandInput.erase(0, 1);
            CurrentCommandType = CommandType::ColourChange_RGB;
        }
        else if (CommandInput[0] == '$')
        {
            value = CommandInput.erase(0, 1);
            CurrentCommandType = CommandType::ColourChange_HSV;
        }
        else if (CommandInput.compare(0, GroupIdentifier.size(), GroupIdentifier) == 0)
        {
            value = CommandInput.erase(0, GroupIdentifier.size());
            CurrentCommandType = CommandType::Group;
        }
        else if (isdigit(CommandInput[0]))
        {
            bool ParsedAmountOfTimesToExecute = false;
            value = "";
            for (char c : CommandInput)
            {
                if (ParsedAmountOfTimesToExecute)
                {
                    value += c;
                }
                else if (isalpha(c))
                {
                    TimesToExecute = std::stoi(value);
                    value = c;
                    ParsedAmountOfTimesToExecute = true;
                }
                else
                {
                    value += c;
                }
            }
            if (ParsedAmountOfTimesToExecute)
            {
                CurrentCommandType = CommandType::FunctionName;
            }
            else
            {
                CurrentCommandType = CommandType::Wait;
            }
        }
        return Command(CurrentCommandType, value, CurrentOperation, TimesToExecute);
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
