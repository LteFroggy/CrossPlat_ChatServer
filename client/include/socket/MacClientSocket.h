#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "socket/IClientSocket.h"

class MacClientSocket : public IClientSocket {
private :
    int socket_fd;

public :
    MacClientSocket();
    ~MacClientSocket();

    void start();
    void stop();
};
