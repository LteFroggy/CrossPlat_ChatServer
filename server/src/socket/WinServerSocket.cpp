#include "socket/WinServerSocket.h"
#include "stdafx.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32");

#define PORT 8080
#define PACKET_SIZE 1024

WinServerSocket* WinServerSocket::instance = nullptr;

// 싱글톤으로, 하나의 인스턴스만 운용하기
WinServerSocket* WinServerSocket::getInstance() {
    if (!instance) {
        instance = new WinServerSocket();
        return instance;
    }
    return instance;
}

// 서버 시작하기
int WinServerSocket::start() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    WSACleanup();

    return 0;
}