#include "socket/MacServerSocket.h"

#include <atomic>
#include <thread>
#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

// MacServerSocket의 싱글턴 인스턴스 포인터 초기화
MacServerSocket* MacServerSocket::instance = nullptr;

// 싱글턴 인스턴스를 반환합니다.
// 이미 생성되어 있으면 기존 인스턴스를 반환하고, 없으면 새로 생성합니다.
MacServerSocket* MacServerSocket::getInstance() {
    if (instance == nullptr) {
        instance = new MacServerSocket();
    }
    return instance;
}

// 서버의 메인 루프: 클라이언트 연결 수락 및 메시지 수신
void MacServerSocket::serverLoop(const int server_fd) const {
    char buffer[1024];
    // 서버가 실행 중일 때 반복
    while (running_.load()) {
        sockaddr_in client_addr{};
        socklen_t addr_len = sizeof(client_addr);
        // 클라이언트 연결을 대기 및 수락합니다.
        const int client_fd = accept(server_fd, reinterpret_cast<sockaddr *>(&client_addr), &addr_len);
        // 연결 실패 시 다음 반복
        if (client_fd < 0) continue;

        // 클라이언트로부터 메시지를 읽어옵니다.
        ssize_t n = read(client_fd, buffer, sizeof(buffer));
        if (n > 0) {
            buffer[n] = '\0'; // 문자열 종료 문자 추가
            cout << "Received message: " << buffer << endl;
        }
        // 클라이언트 소켓 종료
        close(client_fd);
    }
}

// 서버 소켓을 초기화하고, 바인딩 및 리스닝 상태로 만듭니다.
int MacServerSocket::start() {
    // 1. 소켓 생성 (TCP 스트림 소켓)
    listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd_ == -1) {
        cerr << " socket() failed" << endl;
        return -1;
    }

    // 2. 소켓 옵션 설정 (주소 재사용)
    int opt = 1;
    setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 서버 주소 정보 설정
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스에서 접속 허용
    addr.sin_port = htons(8080); // 포트 8080 사용

    // 4. 소켓을 주소에 바인딩
    if (::bind(listen_fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        cerr << " bind() failed" << endl;
        return -1;
    }

    // 5. 소켓을 리스닝 상태로 전환 (최대 5개의 대기 큐)
    if (::listen(listen_fd_, 5) < 0) {
        cerr << " listen() failed" << endl;
        return -1;
    }

    // 6. 서버 루프 실행 플래그 설정 및 스레드 시작
    running_.store(true);
    th_ = thread(&MacServerSocket::serverLoop, this, listen_fd_);
    cout << "Listening on port 8080..." << endl;

    return 0;
}

// 서버를 종료하고 리소스를 정리합니다.
void MacServerSocket::stop() {
    // 이미 종료된 경우 아무 작업도 하지 않음
    if (!running_.load()) return;

    // 서버 루프 종료 신호
    running_.store(false);

    // 리스닝 소켓 종료 및 닫기
    shutdown(listen_fd_, SHUT_RDWR);
    close(listen_fd_);
    listen_fd_ = -1;

    // 서버 스레드가 동작 중이면 종료까지 대기
    if (th_.joinable()) th_.join();
    cout << "Server Stopped" << endl;
}