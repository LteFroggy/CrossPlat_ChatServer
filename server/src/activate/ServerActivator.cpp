#include "activate/ServerActivator.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

// Singleton Instance를 받기 위한 코드
ServerActivator& ServerActivator::getInstance() {
    static ServerActivator instance;
    return instance;
}

// 서버를 활성화한다. 주소 바인딩, Listen상태로 만들고 Accept 루프를 돌린다
int ServerActivator::activateServer(int socket_fd) {
    // 주소 바인딩
    if (this->bindSocket(socket_fd) < 0) {
        cout << "바인딩 실패!" << endl;
        return -1;
    }

    // 리스닝 시작
    if (this->listenSocket(socket_fd) < 0) {
        cout << "리스닝 실패!" << endl;
        return -1;
    }

    isRunning.store(true);

    // Accept를 위한 루프 시작
    acceptThread = thread(&ServerActivator::startAcceptLoop, this, socket_fd);

    return 0;
}

void ServerActivator::deactivateServer(int socket_fd) {
    isRunning.store(false);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    if (acceptThread.joinable()) {
        acceptThread.join();
    }

    cout << "서버 정상 종료 완료" << endl;
}

// 주소를 설정하고, Socket에 바인딩
int ServerActivator::bindSocket(int socket_fd) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080); // 포트 8080 사용
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스에서 접속 허용

    int result = ::bind(socket_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    cout << "Bind 결과 : " << result << endl;

    return result;
}

// 소켓을 Listen 상태로 전환
int ServerActivator::listenSocket(int socket_fd) {
    int result = ::listen(socket_fd, 10);
    cout << "Listen 결과 : " << result << endl;

    return result;
}

void ServerActivator::startAcceptLoop(int socket_fd) {
    while (isRunning.load()) {
        int client_fd = accept(socket_fd, nullptr, nullptr);

        // 서버가 종료되었으면, 루프 종료
        if (!isRunning.load()) break;

        // 클라이언트 연결이 실패했으면 아래의 처리
        if (client_fd < 0) {
            if (errno == EINTR) continue;
            continue;
        }

        // 접속한 클라이언트는 분리된 스레드에서 처리
        thread clientThread(handleClient, client_fd);
        clientThread.detach();
    }
}
