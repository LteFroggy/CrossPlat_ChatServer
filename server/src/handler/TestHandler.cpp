#include "handler/TestHandler.h"

#include <iostream>

using namespace std;

void TestHandler::handleClient(int client_fd) {
    cout << "테스트 핸들러 진입 성공" << endl;
}