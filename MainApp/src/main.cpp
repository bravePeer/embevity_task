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
#include "position_detector.hpp"

int main(int argc, char** argv)
{
    Client c;
    c.connectToServer(SIMULATOR_SERVER);
    c.writeCommand(SpecialCommands::RestartSimulator);

    PositionDetector detector(&c);

    detector.init();
    while (true)
    {
        detector.update();
        getchar();
    }

    // std::cout << "Mean: " << detector.calculatePressureMean() << std::endl;
    // int pressure = 0;
    // float temperature = 0.0f;
    // readPressureTemperature(&c, &pressure, &temperature);
    // std::cout << pressure << " " << temperature << std::endl;
    // readPressureTemperature(&c, &pressure, &temperature);
    // std::cout << pressure << " " << temperature << std::endl;
    
    // c.writeCommand(SpecialCommands::RestartSimulator);
    // c.writeCommand(SpecialCommands::StopSimulator);
    // SimulatorServer ss;
    // ss.waitForConnection();

}