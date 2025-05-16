#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#include "server.hpp"
#include "client.hpp"
#include "sensor.hpp"


int main(int argc, char** argv)
{
    Client c;
    c.connectToServer(SIMULATOR_SERVER);
    // c.writeCommand(SpecialCommands::RestartSimulator);

    readSensorReg(&c, MemoryAddresses::PowerDown);
    setPowerDown(&c, 1);
    readSensorReg(&c, MemoryAddresses::PowerDown);


    readSensorReg(&c, MemoryAddresses::Reset);
    setReset(&c, 1);
    readSensorReg(&c, MemoryAddresses::Reset);

    int pressure = 0;
    float temperature = 0.0f;
    readPressureTemperature(&c, &pressure, &temperature);
    std::cout << pressure << " " << temperature << std::endl;
    readPressureTemperature(&c, &pressure, &temperature);
    std::cout << pressure << " " << temperature << std::endl;
    
    // c.writeCommand(SpecialCommands::RestartSimulator);
    // c.writeCommand(SpecialCommands::StopSimulator);
    // SimulatorServer ss;
    // ss.waitForConnection();

}