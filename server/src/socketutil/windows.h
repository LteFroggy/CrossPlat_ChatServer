#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

class ServerSocket {
private:
    static ServerSocket* instance;
    SOCKET listenSocket;
    bool initialized;
    
    // private 생성자 - 외부에서 생성 불가능
    ServerSocket() : listenSocket(INVALID_SOCKET), initialized(false) {}
public:
    static ServerSocket& getInstance() {
        if (instance == INVALID_SOCKET) {
            instance = new ServerSocket();
        }
        return instance;
    }

}