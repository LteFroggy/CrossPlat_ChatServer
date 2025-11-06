#include <iostream>
#include "socket/MacSocketMaker.h"
#include "activate/ServerActivator.h"

using namespace std;

int main() {
    // 소켓 생성
    MacSocketMaker socketMaker;
    int socket_fd = socketMaker.createSocket();

    // Activator 받아와서 서버 활성화
    ServerActivator& activator = ServerActivator::getInstance();
    activator.activateServer(socket_fd);

    return 0;
}