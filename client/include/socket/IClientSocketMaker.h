#pragma once

class IClientSocketMaker {
public :
    virtual ~IClientSocketMaker() = default;

    virtual int createSocket() = 0;
    virtual void deleteSocket() = 0;
};