
class LightShowPlayer
{
public:
  void PlaySong();

private:
  std::vector<ProgrammableLight> OutputLights;
  std::map<std::string, std::vector<std::string>> LightShow;
  CommandFactory CommandParser;
};
