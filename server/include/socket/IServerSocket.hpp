#pragma once

class IServerSocket {
public :
    virtual ~IServerSocket() = default;

    virtual int start() = 0;
    virtual void stop() = 0;
};
