#define RF24_Sender_Defined

#include "RF24_Sender.h"
#include "utility/RPi/spi.h"
#include "RF24.h"
#include "MiLightRadio.h"
#include "PL1167_nRF24.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
RF24_Sender::RF24_Sender()
{
    std::ifstream input_file;
    input_file.open("RF24_Config.txt");
    std::vector<uint8_t> byte_codes(3);

    int groupID = 0;
    int read_value = 0x00;
    int counter = 0;
    std::cout << "Begin Reading" << std::endl;
    while (input_file >> std::hex >> read_value) {

        if (counter == 0) {
            groupID = read_value;
            counter++;
        } else {
            byte_codes[counter - 1] = read_value;//Conversion needed

            counter++;
            if (counter == 4) {
                Groups[groupID]= byte_codes;
                counter = 0;
            }
        }
    }
    for (std::map<int, std::vector<uint8_t>>::iterator it = Groups.begin(); it != Groups.end(); it++) {
        std::cout << it->first << " " << std::hex <<  int(it->second[0]) << " " << int(it->second[1]) << " " << int(it->second[2]) << std::endl;
    }
    mlr.begin();
}
void RF24_Sender::EmitColour
(const Command CommandItem,
 const std::vector<std::pair<const int, Colour>*> ExpectedOutput)
{

    for (std::pair<const int, Colour>* entry : ExpectedOutput ) {
        std::map<int, std::vector<uint8_t>>::iterator it = Groups.find(entry->first);

        if (it != Groups.end()) {
            uint8_t msg[7]  = {
                0xB8,it->second[0],it->second[1],
                0x00,0x00,0x00,0x00
            };

            //Hue 0x1B is solid Red
            msg[3]  = ((0x1B + (entry->second.Hue)));

            uint8_t middle_point = 0x90;
            uint8_t brightness = middle_point;

            if (entry->second.Brightness > 144) {
                brightness += (entry->second.Brightness - middle_point);

            } else {
                brightness -= (entry->second.Brightness);
            }
            int br = ((brightness + 0x08/2)/0x08)*0x08;
            msg[4]  = uint8_t(br);

            //Decide to make it white,
            if (entry->second.Brightness < threshold){
                msg[5] = it->second[2] + 1;
                send(msg); //Send Group off/on command
            } else if (entry->second.Saturation < white_threshold){
                msg[5] = it->second[2];
                send(msg); //Send Group off/on command
                msg[5] = it->second[2] + 16;
                send(msg); //Send Group off/on command
            } else {
                msg[5] = it->second[2];
                send(msg); //Send Group off/on command
                msg[5]  = 0x0F; //Set Hue CMD
                send(msg); //Send Hue
            }
            msg[5]  = 0x0E; //Set Brightness B
            send(msg); //Send Brightness

        }
    }
}
void RF24_Sender::SetColourForCurrentGroups(const Colour OutputColour)
{
    std::cout << "Set for current called" << std::endl;
}

void RF24_Sender::OnCurrentGroupsUpdate(
    const Command CommandItem,
    std::vector<std::pair<const int, Colour>*>  CurrentGroups)
{
    std::cout << "Set for OCG called" << std::endl;
    PostedNewGroups = false;
}

void RF24_Sender::SpecificCommand(const Command command)
{
    std::cout << command.value << std::endl;
}

void RF24_Sender::overkillSend(const char* message)
{
    static uint8_t outgoingPacket[7];
    static uint8_t outgoingPacketPos = 0;
    memset(outgoingPacket, 0, 7);
    // convert input into bytes
    int index = 0;
    for (int counter = 0; *message; ++message)
    {
        int n = 0;
        if (*message >= 'a' && *message <= 'f')
        {
            n = *message - 'a' + 10;
        }
        else if (*message >= 'A' && *message <= 'F')
        {
            n = *message - 'A' + 10;
        }
        else if (*message >= '0' && *message <= '9')
        {
            n = *message - '0';
        }
        else if (*message == ' ')
        {
            index++;
        }
        else
        {
            std::cout << "cannot decode" << std::endl;
            exit(1);
        }
        outgoingPacket[index] = outgoingPacket[index] * 16 + (unsigned long) n;

        mlr.write(outgoingPacket, sizeof(outgoingPacket));
        delay(0);
        mlr.resend();
        delay(0);
        outgoingPacket[6] += 8;
    }
}

void RF24_Sender::send(const uint8_t message[7])
{
    static uint8_t outgoingPacket[7];
    static uint8_t outgoingPacketPos = 0;

    memset(outgoingPacket, 0, 7);

    for (int i = 0; i < 6; i++)
    {
        int n = 0;
        n = message[i];
        outgoingPacket[i] = message[i];
        //outgoingPacket[i] = outgoingPacket[i] * 16 + (unsigned long) n;
    }

    outgoingPacket[6] = end_byte;
    for (int i = 0; i < 20; i++)
    {
        mlr.write(outgoingPacket, sizeof(outgoingPacket));
        mlr.resend();
    }

    end_byte++;
    //}
}
