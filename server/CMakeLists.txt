cmake_minimum_required(VERSION 3.20)
project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 공용 헤더 경로 공개
set(PUBLIC_INC ${CMAKE_SOURCE_DIR}/include)

# 1) 유틸 라이브러리
# 여기서 util이라는 이름으로 NumberUtil.cpp를 컴파일해두겠다 -> libutil.a라는 정적 파일로 미리 빌드해둠.
# 나중에 target_link_library를 통해 main에 묶임.
add_library(util
        src/util/NumberUtil.cpp
)
# 여기서는 util이라고 이름이 지어진 파일들을 어디서 찾을 수 있는지(루트 경로)를 알려준다.
# 덕분에 util/NumberUtil.hpp라고만 써도 컴파일러가 찾을 수 있게 됨.
target_include_directories(util PUBLIC ${PUBLIC_INC})

# 2) 플랫폼별 소켓 라이브러리 선택
if (WIN32)
    add_library(server_socket
        src/socket/WinServerSocket.cpp
    )
    # WinSock2의 API 버전 명시
    target_compile_definitions(server_socket PRIVATE _WIN32_WINNT=0x0A00)
    # 소켓 연결에 필요한 ws2_32 링크하라고 알려주기
    target_link_libraries(server_socket PRIVATE ws2_32)
else () # Mac OS
    add_library(server_socket
        src/socket/MacServerSocket.cpp
    )
endif()
target_include_directories(server_socket PUBLIC ${PUBLIC_INC})

# 실행 파일 (main.cpp 위치에 맞게 경로 조정)
add_executable(server
    main.cpp
        src/socket/MacServerSocket.cpp
)

# 링크
target_link_libraries(server PRIVATE util server_socket)