#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "special_commands.hpp"
#include "utils.hpp"
#include "exceptions.hpp"

#define DEBUG_PRINT

constexpr const char* SIMULATOR_SERVER = "simulator.server";

class SimulatorServer
{
public:
    SimulatorServer();
    ~SimulatorServer();

    void waitForConnection();

    void receiveData(char * buffer, int* len, SpecialCommands* command);
    void sendResponse(const char* data, int len);

private:
    int serverSocket = -1;
    struct sockaddr_un serverSocketAddress;
    struct sockaddr_un clientSocketAddress;

    int client = -1;
};