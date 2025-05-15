#include "client.hpp"

Client::Client()
{
    std::cout << "Initializing client..." << std::endl;

    clientSocet = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(clientSocet == -1)
        throw std::runtime_error("Socket can not be opened!");    

    clientSocketAddress.sun_family = AF_LOCAL;
    clientSocketAddress.sun_path[0] = 0;
    strncpy(clientSocketAddress.sun_path + 1, SIMULATOR_CLIENT, strlen(SIMULATOR_CLIENT));
    // unlink(SIMULATOR_CLIENT);

    int result = bind(clientSocet, (struct sockaddr*)&clientSocketAddress, sizeof(clientSocketAddress));
    if(result == -1)
    {
        close(clientSocet);
        throw std::runtime_error("Bind error!");
    }

    std::cout << "Client initialized!" << std::endl;
}

Client::~Client()
{
    close(clientSocet);
}

void Client::connectToServer(const char* serverAddress)
{
    std::cout << "Connecting to:" << serverAddress <<std::endl;
    serverSocketAddress.sun_family = AF_LOCAL;
    serverSocketAddress.sun_path[0] = 0;
    strncpy(serverSocketAddress.sun_path + 1, serverAddress, sizeof(serverSocketAddress.sun_path)-2);

    int result = connect(clientSocet, (sockaddr*)&serverSocketAddress, sizeof(sa_family_t) + strlen(serverAddress) + 1);
    if(result == -1)
    {
        close(clientSocet);
        perror("Connect error");
        throw std::runtime_error("Connection error! ");
    }

    std::cout << "Connected to server!" << std::endl;
}

void Client::writeReg(char address, const char* data, int dataLen)
{
    if(dataLen > 16)
        throw "Max send bytes is 16";
    char buffer[17];
    memcpy(buffer + 1, data, dataLen);
    buffer[0] = static_cast<char>(address << 1);
    int res = send(clientSocet, buffer, dataLen + 1, 0);
    if (res == -1)
        throw std::runtime_error("Send error!");

    std::cout << "WriteReg Send: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    res = recv(clientSocet, buffer, sizeof(buffer), 0);
    if(res == -1)
        throw std::runtime_error("Receiving error!");
        
    std::cout << "WriteReg Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    if(res != 3 || !((buffer[0] == '\xff') && (buffer[1] == 'O') && (buffer[2] == 'K')))
        throw std::runtime_error("Wrong respone!");
}

/// @brief 
/// @param address address of device
/// @param data min size is 1
/// @param dataLen 
void Client::readReg(char address, char* data, int* dataLen)
{
    char buffer[17]{0};
    buffer[0] = static_cast<char>(address << 1) | 1;

    int res = send(clientSocet, buffer, *dataLen + 1, 0);
    if (res == -1)
        throw std::runtime_error("Send error!");

    std::cout << "ReadReg Send: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    *dataLen = recv(clientSocet, data, 16, 0);
    if(*dataLen == -1)
        throw std::runtime_error("Receiving error!");

    std::cout << "ReadReg Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
}

void Client::writeCommand(SpecialCommands command)
{
    char buffer[8]{0};
    buffer[0] = 0xff;
    buffer[1] = (char)command;
    int res = send(clientSocet, buffer, 2, 0);
    if (res == -1)
        throw std::runtime_error("Send error!");

    std::cout << "Send: " << res << " bytes to server: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    res = recv(clientSocet, buffer, sizeof(buffer), 0);
    if(res == -1)
        throw std::runtime_error("Receiving error!");
        
    std::cout << "Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    if(res != 3 || !((buffer[0] == '\xff') && (buffer[1] == 'O') && (buffer[2] == 'K')))
        throw std::runtime_error("Wrong respone!");
}