#include <iostream>

#include "socket/MacClientSocketMaker.h"

using namespace std;

int main() {
    MacClientSocketMaker socketMaker = MacClientSocketMaker();

    int socket_fd = socketMaker.createSocket();
    socketMaker.deleteSocket();
}