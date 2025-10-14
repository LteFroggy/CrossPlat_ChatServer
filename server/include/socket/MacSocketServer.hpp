#pragma once
#include "IServerSocket.hpp"
#include <atomic>

class MacServerSocket : public IServerSocket {
private:
      // 외부 초기화 방지
      MacServerSocket() {}
      ~Singleton() {}
public :
  static MacSocketServer* instance;


}