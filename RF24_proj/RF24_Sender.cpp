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
#include "stddef.h"
#include "V2RFEncoding.h"
RF24_Sender::RF24_Sender(MILIGHT_VERSION version)
{
	proxies = ProxyMaker::proxy_filereader("proxy_rf24.txt");
	
    std::ifstream input_file;
    input_file.open("RF24_Config.txt");
    std::vector<uint8_t> byte_codes(3);

    int groupID = 0;
    int read_value = 0x00;
    int counter = 0;
	MILIGHT_VERSION ver = MILIGHT_VERSION::V5;
    std::cout << "Begin Reading" << '\n';
    while (input_file >> std::hex >> read_value)
    {

        if (counter == 0)
        {
            groupID = read_value;
            counter++;
        }
		else if (counter == 1)
		{
			if (read_value == 0x05) {
				ver = MILIGHT_VERSION::V5;
			}
			if (read_value == 0x06) {
				ver = MILIGHT_VERSION::V6;
			}
			counter++;
		}
        else
        {
            byte_codes[counter - 2] = read_value;//Conversion needed

            counter++;
            if (counter == 5)
            {
				std::pair<MILIGHT_VERSION ,std::vector<uint8_t>> pairing = {
					ver,byte_codes
				};
                Groups[groupID] = pairing;
                counter = 0;
            }
        }
    }
   
    //Configure versioning
    this->version = version;

    if (version == MILIGHT_VERSION::V5)
    {
        mlr.begin(CHANNELS_V5);

    }
    if (version == MILIGHT_VERSION::V6)
    {
        mlr.begin(CHANNELS_V6,0x7236,0x1809, 10);
    }
	std::cout << "Setting data rate was: " << radio.setDataRate(RF24_1MBPS) << '\n';
	radio.powerUp();
	

}
void RF24_Sender::EmitColour
(const Command CommandItem,
 const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput)
{
	auto proxiedOutput = ProxyMaker::proxy_maker(ExpectedOutput, proxies);
	

    for (std::pair<const int, colour_combiner>* entry : proxiedOutput )
    {
        std::map<int, std::pair<MILIGHT_VERSION,std::vector<uint8_t>>>::iterator it = Groups.find(entry->first);

        if (it != Groups.end())
        {
            if (version == MILIGHT_VERSION::V6)
            {
                uint8_t msg[9]  =
                {
                    0x00, //Key, no utility in varying it
                    0x20, //ProtocolID
                    it->second.second[0], //deviceId >> 8;
                    it->second.second[1] & 0xFF, //deviceId & 0xFF;
                    0x00, //CMD
                    0x00, //ARG
                    ++seq_num, //sequenceNum++;
                    it->second.second[2], //GroupID 65 is for all groups I find this best
                    0x00
                };

                if (entry->second.brightness_changed())
                {
                    if (entry->second.get_colour().Brightness < threshold)
                    {
                        std::cout << "Turning off" << '\n';
                        msg[4] = 0x01;
                        msg[5] = 0x05;
                        msg[6] = ++seq_num;
                        send_v6(msg); //Send Group off/on command
						break; //Break CURRENT loop, check this is proper later. 
                    }
				}
                if (entry->second.hue_changed())
                {
                    std::cout << "Hue being sent" << '\n';
                    msg[4]  = 0x02;
                    msg[5]  = 0x5F + entry->second.get_colour().Hue;
                    msg[6] =  ++seq_num;
                    send_v6(msg);
                }
                if (entry->second.brightness_changed())
                {
                    if (entry->second.get_colour().Brightness < threshold)
                    {
                        std::cout << "Turning off" << '\n';
                        msg[4] = 0x01;
                        msg[5] = 0x05;
                        msg[6] = ++seq_num;
                        send_v6(msg); //Send Group off/on command
                    }
                    else
                    {
                        std::cout << "Brightness being sent" << '\n';
                        msg[4] = 0x04; //Brightness Command
                        msg[5] = 0x8F + (100 * (float(entry->second.get_colour().Brightness) / 255.0F)); //Brightness arg
                        msg[6] = ++seq_num;
                        send_v6(msg);

                    }
                }
                if (entry->second.sat_changed())
                {
                    std::cout << "Sat being sent" << '\n';
                    msg[4] = 0x04;
                    msg[5] = 0x0D + (100 * (float(entry->second.get_colour().Saturation) / 255.0F));
                    msg[6] = ++seq_num;
                    send_v6(msg);
                }

                seq_num = msg[6];
            }
            if (version == MILIGHT_VERSION::V5)
            {
                const uint8_t middle_point = 0x90;
                uint8_t brightness = middle_point;
                
                if (entry->second.get_colour().Brightness > 144) {
                    brightness = 255;
					brightness -= (entry->second.get_colour().Brightness - middle_point);
                    int remainder = (brightness - 8) % 16;
                    if (remainder > 8) {
                        remainder -= 16;
                    }
                    std::cout << "Rounding " << int(brightness) << " by " << int(remainder);
                    
                    brightness -= remainder; //Brightness must be a multiple of 16
                    std::cout << " to " << int(brightness) << '\n';
				}
				else {
					brightness -= (entry->second.get_colour().Brightness);
                    int remainder = brightness % 16;
                    if (remainder > 8) {
                        remainder -= 16;
                    }
                    
                    std::cout << "Rounding " << int(brightness) << " by " << int(remainder);
                    brightness -= remainder; //Brightness must be a multiple of 16
                    std::cout << " to " << int(brightness) << '\n';
				}
                

                uint8_t msg[7]  =
                {
                    0xB0,
                    it->second.second[0],
                    it->second.second[1],
                    0x00, //Hue byte
                    0x00, //Brightness byte
                    it->second.second[2], //CMD, defaults to GROUPON
                    ++seq_num
                };
				//Should msg[0] be b0 or b8
				
				std::pair<uint8_t,uint8_t> remote_pair = {msg[1], msg[2]};

                //If we gonna do group checking, we would do it here
                //We had this feature previously, but I don't think we need it anymore,
                //This factoid needs to be confirmed.
				if (entry->second.brightness_changed() && entry->second.get_colour().Brightness <= threshold) {
						std::cout << "Turning Light Off" << '\n';
						msg[5]++;
						send_V5(msg); //Send Group off
						break; //We need to stop running this chunk, light is now off!
                }
                else if (entry->second.get_colour().Brightness > threshold) {

                    if (entry->second.prev_colour().Brightness < threshold) {
                        std::cout << "Turning Light On" << '\n';
                        send_V5(msg);
                    }

                    if (entry->second.sat_changed() && entry->second.get_colour().Saturation < white_threshold)
                    {
                        std::cout << "Making light white" << '\n';
                        msg[5] += 16;
                        send_V5(msg); //Send white command
                        msg[5] -= 16;
                    } else if (
                        entry->second.hue_changed() | 
                        (entry->second.prev_colour().Saturation < white_threshold && 
                        entry->second.get_colour().Saturation > white_threshold) 
                    ) {
                        std::cout << "Sending brightness packet" << '\n';
                        msg[3] = 0x1B + (entry->second.get_colour().Hue);
                        msg[5]  = 0x0F; //Set Hue CMD
                        send_V5(msg); //Send Hue		
                    }

                    if (entry->second.brightness_changed())
                    {
                        std::cout << "Only brightness changes of 16 are recognised ";
                        //We only send brightness if we have have a proper change
                        if (entry->second.get_colour().Brightness >= entry->second.prev_colour().Brightness + 16 |
                            entry->second.get_colour().Brightness <= entry->second.prev_colour().Brightness - 16 )
                            {
                                std::cout << "Sending brightness packet" << '\n';
                                msg[3]  = 0x00; //Not needed, will experiement if this is useful
                                msg[4]  = brightness;
                                msg[5]  = 0x0E; //Set Brightness Byte
                                send_V5(msg); //Send Brightness
                            }
                    }
                }
            }
        }
    }
}
void RF24_Sender::SetColourForCurrentGroups(const Colour OutputColour)
{
    std::cout << "Set for current called" << '\n';
}

void RF24_Sender::OnCurrentGroupsUpdate(
    const Command CommandItem,
    std::vector<std::pair<const int, colour_combiner>*>  CurrentGroups)
{
    std::cout << "Set for OCG called" << '\n';
    PostedNewGroups = false;
}

void RF24_Sender::SpecificCommand(const Command command)
{
    //Expand this to additional cmds
    std::cout << command.value << '\n';
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
            std::cout << "cannot decode" << '\n';
            exit(1);
        }
        outgoingPacket[index] = outgoingPacket[index] * 16 + (unsigned long) n;
		//mlr.write(outgoingPacket, sizeof(outgoingPacket),CHANNELS);
        //mlr.write(outgoingPacket, sizeof(outgoingPacket),CHANNELS);
        delay(0);
       // mlr.resend(CHANNELS);
        delay(0);
        outgoingPacket[6] += 8;
    }
}

void RF24_Sender::send_v6(uint8_t* message)
{
    V2RFEncoding::encodeV2Packet(message);
	prf.setSyncword(0x7236,0x1809);
    prf.setMaxPacketLength(10);
	
    send(message, CHANNELS_V6);
}

void RF24_Sender::send_V5(uint8_t* message) {
	prf.setSyncword(0x147A, 0x258B);
    prf.setMaxPacketLength(8);
	send(message, CHANNELS_V5);

}

void RF24_Sender::send(const uint8_t* message, uint8_t* CHANNELS)
{
    uint8_t outgoingPacket[packet_size];
    uint8_t outgoingPacketPos = 0;
    memset(outgoingPacket, 0, packet_size);

    for (int i = 0; i < packet_size; i++)
    {
        outgoingPacket[i] = message[i];
        std::cout << (int)(message[i]) << " ";
    }
    std::cout << '\n';
    mlr.write(outgoingPacket, sizeof(outgoingPacket), CHANNELS);

    for (int i = 0; i < 15; i++)
    {
		delay(10);
	    mlr.resend(CHANNELS);
    }
};
