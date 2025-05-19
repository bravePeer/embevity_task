#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>

#include "exceptions.hpp"
#include "special_commands.hpp"
#include "utils.hpp"

constexpr const char* SIMULATOR_CLIENT = "simulator.client";

class Client
{
public:
    Client();
    ~Client();

    void connectToServer(const char* serverAddress);

    void writeReg(char address, const char* data, int dataLen);
    void readReg(char address, char* data, int* dataLen);

    void writeCommand(SpecialCommands command);

private:
    struct sockaddr_un clientSocketAddress;
    struct sockaddr_un serverSocketAddress;
    int clientSocet = -1;
};