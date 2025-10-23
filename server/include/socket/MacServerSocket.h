#pragma once
#include "socket/IServerSocket.hpp"
#include <atomic>
#include <thread>


class MacServerSocket : public IServerSocket {
private:
  static MacServerSocket* instance; // 싱글톤을 위한 instance
  std::atomic<bool> running_{false}; // 서버 실행중인가?
  int listen_fd_ = -1; // 열린 서버 핸들
  std::thread th_; // 실행할 스레드

  // 외부 초기화 방지
  MacServerSocket() = default;
public :
  static MacServerSocket* getInstance();
  int start() override;
  void stop() override;

private :
  // Start 후 Thread 기반으로 Accept 할 녀석
  void serverLoop(int server_fd) const;
};