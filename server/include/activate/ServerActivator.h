#pragma once
#include <atomic>
#include <thread>

using namespace std;

class ServerActivator {
public :
    static ServerActivator& getInstance();

    int activateServer(int socket_fd);
    void deactivateServer(int socket_fd);

private :
    atomic<bool> isRunning = false;
    thread acceptThread;

    ServerActivator() = default;
    ServerActivator(const ServerActivator&) = delete;
    ServerActivator& operator=(const ServerActivator&) = delete;

    int bindSocket(int socket_fd);
    int listenSocket(int socket_fd);
    void startAcceptLoop(int socket_fd);
};
