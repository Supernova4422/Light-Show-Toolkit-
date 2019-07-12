
#include "BL_433.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

BL_433::BL_433()
{
    std::ifstream myConfig("BL_433_CONFIG.txt");
    myConfig >> repeats;

    std::cout << "433 Config";
    std::cout << "    Repeats: ";
    std::cout << std::to_string(repeats);
    std::cout << std::endl;

    std::ifstream myfile("BL_433_GROUPS.txt");
    for (int read_value = 0x00; myfile >> read_value;)
    {
        int on_val = 0;
        int off_val = 0;
        myfile >> val;
        myfile >> val;

        on_cmds[read_value] = on_val;
        off_cmds[read_value] = off_val;
        std::cout << "    " << std::to_string(read_value) << ":" << on_val << "," << off_val << std::endl;
    }

    if (wiringPiSetup() != -1)
    {
        mySwitch.enableTransmit(0);
        std::cout << "Initialised WiringPi, 433 Transmitter as well" << std::endl;
    }

    mySwitch.disableReceive();
    mySwitch.setRepeatTransmit(repeats);
}

void BL_433::initialise()
{
    std::cout << "Please ensure that you have run this program using sudo" << std::endl;
    std::cout << "433mhz sender is ready" << std::endl;
}

void BL_433::turnon(int group)
{
    std::cout << on_cmds[group] << std::endl;
    if (on_cmds[group] != 0)
    {
        mySwitch.send(on_cmds[group], 24);
    }
}

void BL_433::turnoff(int group)
{
    std::cout << off_cmds[group] << std::endl;
    if (off_cmds[group] != 0)
    {
        mySwitch.send(off_cmds[group], 24);
    }
}
