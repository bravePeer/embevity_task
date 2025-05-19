#include "server.hpp"

SimulatorServer::SimulatorServer()
{
    // memset(&address, 0, sizeof(address));
#ifdef DEBUG_PRINT
    std::cout << "Initializing server..." << std::endl;
#endif

    serverSocket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(serverSocket == -1)
        throw SocketError(strerror(errno)); 

    serverSocketAddress.sun_family = AF_LOCAL;
    serverSocketAddress.sun_path[0] = 0;
    strncpy(serverSocketAddress.sun_path + 1, SIMULATOR_SERVER, sizeof(serverSocketAddress.sun_path)-2);
    // unlink(SIMULATOR_SERVER);

    int result = bind(serverSocket, (struct sockaddr*)&serverSocketAddress, sizeof(sa_family_t) + strlen(SIMULATOR_SERVER) + 1);
    if(result == -1)
    {
        close(serverSocket);
        throw BindError(strerror(errno));
    }

    result = listen(serverSocket, 1);
    if(result == -1)
    {
        close(serverSocket);
        throw ListenError(strerror(errno));
    }

#ifdef DEBUG_PRINT
    std::cout << "Server initialized, socet name:" << SIMULATOR_SERVER << std::endl;
#endif
}

SimulatorServer::~SimulatorServer()
{
    close(serverSocket);
    close(client);

#ifdef DEBUG_PRINT
   std::cout << "Server closed" << std::endl;
#endif
}

void SimulatorServer::waitForConnection()
{
#ifdef DEBUG_PRINT
    std::cout << "Waiting for connection" << std::endl;
#endif

    client = accept(serverSocket, nullptr, nullptr);
    if(client == -1)
    {
        close(serverSocket);
        close(client);
        throw ConnectionError(strerror(errno));
    }

#ifdef DEBUG_PRINT
    std::cout << "Connected to client at: " << clientSocketAddress.sun_path << std::endl; 
#endif
}

void SimulatorServer::receiveData(char* buffer, int* len, SpecialCommands* command)
{
    int res = static_cast<int>(recv(client, buffer, *len, 0));
    if(res == -1)
        throw ReceiveError(strerror(errno));
        
#ifdef DEBUG_PRINT
    std::cout << "Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;
#endif

    *len = res;
    
    if(buffer[0] == '\xff')
    {
        *command = static_cast<SpecialCommands>(buffer[1]);
    }
}

void SimulatorServer::sendResponse(const char* data, int len)
{
    int res = static_cast<int>(send(client, data, len, 0));
    if(res == -1)
        throw SendError(strerror(errno));

#ifdef DEBUG_PRINT
    std::cout << "Send: " << res << " bytes: ";
    printCharArray(data, res);
    std::cout << std::endl;
#endif
}

