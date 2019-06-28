
#include "FileReader.h"
class LightShowFileReader : public FileReader
{
public:
  std::map<std::string, std::vector<std::string>> ProcessFile(const std::string &FilePath);

private:
  std::vector<std::string> SplitLineIntoCommands(const std::string &Line);
  std::vector<std::string> CleanUpCommands(const std::vector<std::string> &StringVector);
};
