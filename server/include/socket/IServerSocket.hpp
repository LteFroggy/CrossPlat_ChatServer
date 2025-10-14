#pragma once
#include <cstdint>

class ISocketServer {
public :
    virtual ~ISocketServer() = default;

    virtual void start(int port) = 0;
    virtual void stop() = 0;
}