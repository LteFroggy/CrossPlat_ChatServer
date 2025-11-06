#include "socket/MacSocketMaker.h"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

// 서버 소켓을 생성하고 그 결과를 반환합니다.
int MacSocketMaker::createSocket() {
    // 이미 소켓이 열려있으면, 그대로 반환
    if (socket_fd != -1) {
        return socket_fd;
    }

    // 1. 소켓 생성 (TCP 스트림 소켓)
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        cerr << " socket() failed" << endl;
        return -1;
    }

    // 2. 소켓 옵션 설정 (디버깅 편의성을 위해 주소 재사용을 허용함)
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 소켓 fd 반환
    return socket_fd;
}

// 서버를 종료하고 리소스를 정리합니다.
void MacSocketMaker::deleteSocket() {
    // 소켓 존재하지 않으면 아무것도 안하기
    if (socket_fd == -1) return;

    // 소켓 닫기
    close(socket_fd);
    socket_fd = -1;
}