#pragma once
#include <thread>

#include "socket/IServerSocket.h"

class WinServerSocket : public IServerSocket {
private:
    static WinServerSocket* instance; // 싱글톤을 위한 instance
    std::atomic<bool> running_{false}; // 서버 실행중인가?
    int listen_fd_ = -1; // 열린 서버 핸들
    std::thread th_; // 실행할 스레드

    // 외부 초기화 방지
    WinServerSocket() = default;
public :
    static WinServerSocket* getInstance();
    int start() override;
    void stop() override;
}