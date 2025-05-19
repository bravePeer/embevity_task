#pragma once
#include <stdexcept>

class CommunicationError : public std::exception
{
public:
    explicit CommunicationError(const char* msg);

    const char* what() const _GLIBCXX_NOTHROW override;
private:
    std::string message;
};

class SocketError : public CommunicationError
{
public:
    explicit SocketError(const char* msg);
};

class BindError : public CommunicationError
{
public:
    explicit BindError(const char* msg);
};

class ListenError : public CommunicationError
{
public:
    explicit ListenError(const char* msg);
};

class ConnectionError : public CommunicationError
{
public:
    explicit ConnectionError(const char* msg);
};

class SendError : public CommunicationError
{
public:
    explicit SendError(const char* msg);
};

class ReceiveError : public CommunicationError
{
public:
    explicit ReceiveError(const char* msg);
};

class ReceiveValueError : public CommunicationError
{
public:
    explicit ReceiveValueError(const char* msg);
};
