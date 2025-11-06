#include "socket/WinSocketMaker.h"
#include "stdafx.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32");

// 싱글톤으로, 하나의 인스턴스만 운용하기

int WinSocketMaker::createSocket() {
    // 윈도우 환경에서 소켓 생성 후 socket_fd 반환하도록
}

void WinSocketMaker::deleteSocket() {
    // 윈도우 환경에서 소켓 할당 해제하도록
}