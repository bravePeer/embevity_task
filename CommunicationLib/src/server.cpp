#include "server.hpp"

SimulatorServer::SimulatorServer()
{
    // memset(&address, 0, sizeof(address));
    std::cout << "Initializing server..." << std::endl;

    serverSocket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(serverSocket == -1)
        throw std::runtime_error("Socket can not be opened!"); 

    serverSocketAddress.sun_family = AF_LOCAL;
    serverSocketAddress.sun_path[0] = 0;
    strncpy(serverSocketAddress.sun_path + 1, SIMULATOR_SERVER, sizeof(serverSocketAddress.sun_path)-2);
    // unlink(SIMULATOR_SERVER);

    int result = bind(serverSocket, (struct sockaddr*)&serverSocketAddress, sizeof(sa_family_t) + strlen(SIMULATOR_SERVER) + 1);
    if(result == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Bind error!");
    }

    result = listen(serverSocket, 1);
    if(result == -1)
    {
        close(serverSocket);
        throw std::runtime_error("Listen error!");
    }

    std::cout << "Server initialized, socet name:" << SIMULATOR_SERVER << std::endl;
}

SimulatorServer::~SimulatorServer()
{
    close(serverSocket);
    close(client);
    std::cout << "Server closed" << std::endl;
}

void SimulatorServer::waitForConnection()
{
    std::cout << "Waiting for connection" << std::endl;
    socklen_t len = sizeof(clientSocketAddress);
    client = accept(serverSocket, nullptr, nullptr);
    if(client == -1)
    {
        close(serverSocket);
        close(client);
        throw std::runtime_error("Client connection error!");
    }

    std::cout << "Connected to client at: " << clientSocketAddress.sun_path << std::endl; 
}

void SimulatorServer::receiveData(char* buffer, int* len, SpecialCommands* command)
{
    int res = recv(client, buffer, *len, 0);
    if(res == -1)
        throw std::runtime_error("Receiving error!");

    std::cout << "Received: " << res << " bytes: ";
    printCharArray(buffer, res);
    std::cout << std::endl;

    *len = res;
    
    if(buffer[0] == '\xff')
    {
        *command = static_cast<SpecialCommands>(buffer[1]);
    }
}

void SimulatorServer::sendResponse(const char* data, int len)
{
    int res = send(client, data, len, 0);
    if(res == -1)
        throw std::runtime_error("Send error!");
}

