#include <string>
class AudioPlayer_Dummy
{
	public:
	void stopSong() {};
	bool playSong(std::string filename, unsigned int songStartAt) {
		std::cout << "Playing: " << filename << " at " << std::to_string(songStartAt) <<  std::endl;
		return true;
	};
};