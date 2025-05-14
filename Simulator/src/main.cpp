#include <iostream>
#include "server.hpp"

int main()
{
    SimulatorServer server;
    server.waitForConnection();

    bool running = true;
    while (running)
    {
        char buffer[64]{0};
        int len = 64;
        SpecialCommands command = SpecialCommands::None;
        server.receiveData(buffer, &len, &command);
        
        if(len == 0)
        {
            server.waitForConnection();
            continue;
        }

        switch (command)
        {
        case SpecialCommands::None:
            // process standard I2C communication
            break;
        case SpecialCommands::ReloadFile:
            server.sendResponse("\xffOK", 3);
            break;
        case SpecialCommands::RestartSimulator:
            server.sendResponse("\xffOK", 3);
            break;
        case SpecialCommands::StopSimulator:
            running = false;
            server.sendResponse("\xffOK", 3);
        break;
        default:
            break;
        }

    }
    
}