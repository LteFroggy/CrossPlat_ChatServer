#pragma once
#include <thread>

#include "socket/ISocketMaker.h"

class WinSocketMaker : public ISocketMaker {
    int socket_fd = -1;

public :
    int createSocket() override;
    void deleteSocket() override;
};