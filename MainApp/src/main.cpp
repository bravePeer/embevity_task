#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

// #include "../../CommunicationLib/include/server.hpp"
#include "server.hpp"
#include "client.hpp"

int main(int argc, char** argv)
{
    // if(argc < 2)
    // {
    //     std::cout << "Pass Simulator PID as argument!" << std::endl;
    // }
    // pid_t simulatorPid = atoi(argv[1]);
    // std::cout << "Simulator PID: "<< simulatorPid << std::endl;

    Client c;
    c.connectToServer(SIMULATOR_SERVER);
    c.writeCommand(SpecialCommands::RestartSimulator);
    char buffer[16]{0};
    int len = 1;

    buffer[0] = 0x12;
    c.writeReg(0b1011101, buffer, 1); // Set read reg
    c.readReg(0b1011101, buffer, &len);

    std::cout<<"Reg val = ";
    printCharArray(buffer, len);
    std::cout << std::endl;

    buffer[0] = 0x12;
    buffer[1] = 1;
    c.writeReg(0b1011101, buffer, 2); // Set read reg
    
    buffer[0] = 0x12;
    c.writeReg(0b1011101, buffer, 1); // Set read reg
    c.readReg(0b1011101, buffer, &len);

    std::cout<<"Reg val = ";
    printCharArray(buffer, len);
    std::cout << std::endl;

    c.writeCommand(SpecialCommands::RestartSimulator);
    c.writeCommand(SpecialCommands::StopSimulator);
    // SimulatorServer ss;
    // ss.waitForConnection();

}