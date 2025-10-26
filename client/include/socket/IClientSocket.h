#pragma once

class IClientSocket {
public :
    virtual ~IClientSocket() = default;

    virtual void start();
    virtual void stop();
};