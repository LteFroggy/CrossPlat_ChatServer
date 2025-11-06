#pragma once
#include "socket/IClientSocketMaker.h"

class MacClientSocketMaker : public IClientSocketMaker {
public :
    MacClientSocketMaker() = default;
    ~MacClientSocketMaker() override = default;


    int createSocket() override;
    void deleteSocket() override;
};
