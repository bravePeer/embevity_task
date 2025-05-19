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
    ui.printInfo("Connected to simulator");

    PositionDetector detector(&c);

    bool running = true;
    int simulating = 0; // How many times simulator run
    while (running)
    {
        if(simulating)
        {
            int floorChange = detector.update();
            ui.printResults(floorChange, detector.getPressure(), detector.getTemperature());

            usleep(100000); // Fake sleep to see results
            simulating--;
            continue;
        }

        UI::Command command = ui.processInput();

        switch (command)
        {
        case UI::Command::Init:
            detector.init();
            ui.printInfo("Detector initialized");
            break;
        case UI::Command::Run:
            if(detector.isInitialized())
                simulating = ui.getValueToSet();
            else
                ui.printError("Detector is not initialized");
            break;
        case UI::Command::SetMeasurementsCount:
            detector.setMeasurementCount(ui.getValueToSet());
            ui.printValueChanged("MeasurementCount", ui.getValueToSet());
            break;
        case UI::Command::SetSensivity:
            detector.setSensivityChange(ui.getValueToSet());
            ui.printValueChanged("Sensivity", ui.getValueToSet());
            break;
        case UI::Command::Reset:
            c.writeCommand(SpecialCommands::RestartSimulator);
            detector.deinit();
            ui.printInfo("Reseted simulator");
            break;
        case UI::Command::Exit:
            running = false;
            ui.printInfo("Exiting...");
            break;
        case UI::Command::None:
            ui.printError("Wrong command");
        case UI::Command::Help:
        default:
            ui.printHelp();
            break;
        }
    }
    detector.deinit();
}