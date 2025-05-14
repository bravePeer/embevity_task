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
    c.writeCommand(SpecialCommands::RestartSimulator);
    c.writeCommand(SpecialCommands::StopSimulator);
    // SimulatorServer ss;
    // ss.waitForConnection();

}