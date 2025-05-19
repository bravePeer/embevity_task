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
#include "ui.hpp"

int main(int argc, char** argv)
{
    UI ui;

    Client c;
    c.connectToServer(SIMULATOR_SERVER);
    c.writeCommand(SpecialCommands::RestartSimulator);

    PositionDetector detector(&c);

    detector.init();
    bool running = true;
    int simulating = 0; // How many times simulator run
    while (running)
    {
        // detector.update();
        // getchar();

        if(simulating)
        {
            int t = detector.update();
            if(t > 0)
            {
                std::cout << "Floor up" << std::endl;
            }
            else if(t < 0)
            {
                std::cout << "Floor down" << std::endl;
            }
            usleep(1000);
            simulating--;
            continue;
        }

        UI::Command command = ui.processInput();

        switch (command)
        {
        case UI::Command::Run:
            detector.init();
            simulating = ui.getValueToSet();
            break;
        case UI::Command::SetMeasurementsCount:
            detector.setMeasurementCount(ui.getValueToSet());
            break;
        case UI::Command::SetSensivity:
            detector.setSensivityChange(ui.getValueToSet());
            break;
        case UI::Command::Reset:
            c.writeCommand(SpecialCommands::RestartSimulator);
            // detector.reset();
            break;
        case UI::Command::Exit:
            running = false;
            break;
        case UI::Command::None:
        default:
            ui.printHelp();
            break;
        }
    }
    detector.deinit();
}