#include "exceptions.hpp"

CommunicationError::CommunicationError(const char* msg)
    : message(msg)
{ }

const char* CommunicationError::what() const _GLIBCXX_NOTHROW
{
    return message.c_str();
}

SocketError::SocketError(const char* msg)
    : CommunicationError(msg)
{ }

BindError::BindError(const char* msg)
    : CommunicationError(msg)
{ }

ListenError::ListenError(const char* msg)
    : CommunicationError(msg)
{ }

ConnectionError::ConnectionError(const char* msg)
    : CommunicationError(msg)
{ }

SendError::SendError(const char* msg)
    : CommunicationError(msg)
{ }

ReceiveError::ReceiveError(const char* msg)
    : CommunicationError(msg)
{ }

ReceiveValueError::ReceiveValueError(const char* msg)
    : CommunicationError(msg)
{ }
