#pragma once

class ISocketMaker {
public :
    virtual ~ISocketMaker() = default;

    virtual int createSocket() = 0;
    virtual void deleteSocket() = 0;
};
