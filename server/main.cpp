#include <iostream>
#include "socket/MacServerSocket.hpp"

using namespace std;

int main() {
    MacServerSocket* socket = MacServerSocket::getInstance();

    socket->start();

    socket->stop();

    return 0;
}