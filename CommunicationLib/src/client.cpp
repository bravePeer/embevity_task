#include "client.hpp"
#include <signal.h>

Client::Client()
{
#ifdef DEBUG_PRINT
    std::cout << "Initializing client..." << std::endl;
#endif
    signal(SIGPIPE, SIG_IGN);
    
    clientSocet = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(clientSocet == -1)
        throw SocketError(strerror(errno));    

    clientSocketAddress.sun_family = AF_LOCAL;
    clientSocketAddress.sun_path[0] = 0;
    strncpy(clientSocketAddress.sun_path + 1, SIMULATOR_CLIENT, strlen(SIMULATOR_CLIENT));
    // unlink(SIMULATOR_CLIENT);

    int result = bind(clientSocet, (struct sockaddr*)&clientSocketAddress, sizeof(clientSocketAddress));
    if(result == -1)
    {
        close(clientSocet);
        throw BindError(strerror(errno));
    }
#ifdef DEBUG_PRINT
    std::cout << "Client initialized!" << std::endl;
#endif
}

Client::~Client()
{
    close(clientSocet);
}

void Client::connectToServer(const char* serverAddress)
{
#ifdef DEBUG_PRINT
  std::cout << "Connecting to:" << serverAddress <<std::endl;
#endif
    serverSocketAddress.sun_family = AF_LOCAL;
    serverSocketAddress.sun_path[0] = 0;
    strncpy(serverSocketAddress.sun_path + 1, serverAddress, sizeof(serverSocketAddress.sun_path)-2);

    int result = connect(clientSocet, (sockaddr*)&serverSocketAddress, 
        static_cast<socklen_t>(sizeof(sa_family_t) + strlen(serverAddress) + 1));
        
    if(result == -1)
    {
        close(clientSocet);
        throw ConnectionError(strerror(errno));
    }

#ifdef DEBUG_PRINT
    std::cout << "Connected to server!" << std::endl;
#endif
}

void Client::writeReg(char address, const char* data, int dataLen)
{
    if(dataLen > 16)
        throw std::invalid_argument("Max send bytes is 16");

    char buffer[17];
    memcpy(buffer + 1, data, dataLen);
    buffer[0] = static_cast<char>(address << 1);
    int res = static_cast<int>(send(clientSocet, buffer, dataLen + 1, 0));
    if (res == -1)
        throw SendError(strerror(errno));

#ifdef DEBUG_PRINT
    std::cout << "WriteReg Send: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    res = static_cast<int>(recv(clientSocet, buffer, sizeof(buffer), 0));
    if(res == -1)
        throw ReceiveError(strerror(errno));
        
#ifdef DEBUG_PRINT
    std::cout << "WriteReg Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    if(res != 3 || !((buffer[0] == '\xff') && (buffer[1] == 'O') && (buffer[2] == 'K')))
        throw ReceiveValueError(strerror(errno));
}

/// @brief 
/// @param address address of device
/// @param data min size is 1
/// @param dataLen how many bytes to read
void Client::readReg(char address, char* data, int* dataLen)
{
    char buffer[17]{0};
    buffer[0] = static_cast<char>(address << 1) | 1;

    int res = static_cast<int>(send(clientSocet, buffer, *dataLen + 1, 0));
    if (res == -1)
        throw SendError(strerror(errno));

#ifdef DEBUG_PRINT
    std::cout << "ReadReg Send: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    *dataLen = static_cast<int>(recv(clientSocet, data, 16, 0));
    if(*dataLen == -1)
        throw ReceiveError(strerror(errno));

#ifdef DEBUG_PRINT
    std::cout << "ReadReg Received: " << *dataLen << " bytes: ";
    printCharArray(data, *dataLen);
    std::cout << std::endl;
#endif
}

void Client::writeCommand(SpecialCommands command)
{
    char buffer[8]{0};
    buffer[0] = 0xff;
    buffer[1] = (char)command;
    int res = static_cast<int>(send(clientSocet, buffer, 2, 0));
    if (res == -1)
        throw SendError(strerror(errno));

#ifdef DEBUG_PRINT
    std::cout << "Send: " << res << " bytes to server: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    res = static_cast<int>(recv(clientSocet, buffer, sizeof(buffer), 0));
    if(res == -1)
        throw ReceiveError(strerror(errno));
        
#ifdef DEBUG_PRINT
    std::cout << "Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    if(res != 3 || !((buffer[0] == '\xff') && (buffer[1] == 'O') && (buffer[2] == 'K')))
        throw ReceiveValueError(strerror(errno));
}