#include <iostream>
#include "server.hpp"
#include "BM1390GLV_ZTR.hpp"

int main()
{
    BM1390GLV_ZTR bm;
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
        {
            // process standard I2C communication
            int shouldAnswer = 0;
            bm.processI2C(buffer, &len, &shouldAnswer);

            if(shouldAnswer)
            {
                server.sendResponse(buffer, len);
            }
            else
                server.sendResponse("\xffOK", 3);


            break;
        }
        case SpecialCommands::ReloadFile:
            server.sendResponse("\xffOK", 3);
            std::cout << "ReloadFile" << std::endl;
            break;
        case SpecialCommands::RestartSimulator:
            server.sendResponse("\xffOK", 3);
            std::cout << "RestartSimulator" << std::endl;
            break;
        case SpecialCommands::StopSimulator:
            running = false;
            server.sendResponse("\xffOK", 3);
            std::cout << "StopSimulator" << std::endl;
            break;
        default:
            break;
        }

    }
    
}