#ifndef RF24_SENDER_H
#define RF24_SENDER_H
#include "utility/RPi/spi.h"
#include "RF24.h"
#include "MiLightRadio.h"
#include "PL1167_nRF24.h"
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
#include <vector>
class RF24_Sender : public ProgrammableLight
{
public:
    RF24_Sender();
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Command CommandItem, const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
    void SpecificCommand(const Command command);
    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups);
private:
    RF24 radio = RF24(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_1MHZ);
    PL1167_nRF24 prf = PL1167_nRF24(radio);
    MiLightRadio mlr= MiLightRadio(prf);
    void overkillSend(const char* message);
    void send(const uint8_t message[7]);
    bool PostedNewGroups = false;

    uint8_t end_byte = 0x00;
    uint8_t threshold = 0x08;
    uint8_t white_threshold = 10;

    std::map<int, std::vector<uint8_t>> Groups;
};

#endif // RF24_SENDER_H
