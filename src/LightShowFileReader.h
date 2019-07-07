
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
class LightShowFileReader
{
public:
  std::map<std::string, std::vector<std::string>> ParseFile(const std::string &FilePath) const
  {
    std::ifstream myfile(FilePath);

    std::map<std::string, std::vector<std::string>> FunctionsWithCommands;
    if (myfile.is_open())
    {
      bool outsideFunction = true;
      std::string CurrentLine;
      std::string CurrentFunctionName;
      std::vector<std::string> CurrentCommandList;
      const std::vector<char> delimeters = {',', ' ', ':'};
      while (getline(myfile, CurrentLine))
      {
        char PreviousChar = 0;
        std::string CurrentWord;
        for (const char CurrentChar : CurrentLine)
        {
          if (CurrentChar == '\r')
          {
            continue;
          }
          else if (CurrentChar == '/' && PreviousChar == '/')
          {
            CurrentWord = CurrentWord.substr(0, CurrentWord.size() - 1);
            break;
          }
          else if (CurrentChar == '{' && outsideFunction)
          {
            CurrentFunctionName = CurrentWord;
            CurrentWord = "";
            outsideFunction = false;
          }
          else if (CurrentChar == '}' && (outsideFunction == false))
          {
            CurrentCommandList.push_back(CurrentWord);
            FunctionsWithCommands.insert(std::make_pair(CurrentFunctionName, CurrentCommandList));
            CurrentCommandList.clear();
            CurrentWord = "";
            CurrentFunctionName = "";
            outsideFunction = true;
          }
          else if (std::find(delimeters.begin(), delimeters.end(), CurrentChar) != delimeters.end() &&
                   (outsideFunction == false) &&
                   CurrentWord != "")
          {
            CurrentCommandList.push_back(CurrentWord);
            CurrentWord = "";
          }
          else
          {
            CurrentWord += CurrentChar;
          }

          PreviousChar = CurrentChar;
        }
        if (CurrentWord != "")
        {
          CurrentCommandList.push_back(CurrentWord);
          CurrentWord = "";
        }
      }
    }
    return FunctionsWithCommands;
  }
};
