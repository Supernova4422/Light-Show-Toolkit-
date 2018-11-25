#ifndef RF24_SENDER_H
#define RF24_SENDER_H

#include "utility/RPi/spi.h"
#include "RF24.h"
#include <map>
#include "PL1167_nRF24.h"
#include "MiLightRadio.h"
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
#include "Color_Combiner.cpp"
#include <vector>
enum MILIGHT_VERSION {V5, V6};
class RF24_Sender : public ProgrammableLight
{
public:
    RF24_Sender(MILIGHT_VERSION version);

    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Command CommandItem, const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput);
    void SpecificCommand(const Command command);
    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, colour_combiner>*>  CurrentGroups);

private:
    std::map<std::set<int>, int, cmpBySetSize> proxies;
    RF24 radio = RF24(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_1MHZ);
    PL1167_nRF24 prf = PL1167_nRF24(radio);
    MiLightRadio mlr= MiLightRadio(prf);
    void overkillSend(const char* message);
    void send(const uint8_t* message, uint8_t* CHANNELS);
    void send_v6(uint8_t* message);
	void send_V5(uint8_t* message);
    bool PostedNewGroups = false;
    MILIGHT_VERSION version = MILIGHT_VERSION::V5;
    uint8_t end_byte = 0x00;
    uint8_t seq_num = 0x00;
    uint8_t threshold = 0x08;
    uint8_t white_threshold = 10;
    uint8_t CHANNELS_V5[3] = {9, 40, 71};
	uint8_t CHANNELS_V6[3] = {70, 39, 8};
	std::map<std::pair<uint8_t,uint8_t>,uint8_t> last_group;

    int packet_size = 7;


    std::map<int, std::pair<MILIGHT_VERSION,std::vector<uint8_t>>> Groups;
};

#endif // RF24_SENDER_H
