# 공용 헤더 경로 공개
set(server_root ${CMAKE_SOURCE_DIR}/server)
set(PUBLIC_INC ${server_root}/include)


# 1) 플랫폼별 소켓 라이브러리 선택
if (WIN32)
    add_library(server_socket
            src/socket/WinSocketMaker.cpp
    )
    # WinSock2의 API 버전 명시
    target_compile_definitions(server_socket PRIVATE _WIN32_WINNT=0x0A00)
    # 소켓 연결에 필요한 ws2_32 링크하라고 알려주기
    target_link_libraries(server_socket PRIVATE ws2_32)
else () # Mac OS
    add_library(server_socket
            src/socket/MacSocketMaker.cpp
    )
endif()
target_include_directories(server_socket PUBLIC ${PUBLIC_INC})

# 2) 소켓을 바인딩, 리슨, Accept처리하는 파일 추가
add_library(activator
        src/activate/ServerActivator.cpp
)
target_include_directories(activator PUBLIC ${PUBLIC_INC})

# 3) 테스트 핸들러 추가
add_library(test_handler
        src/handler/TestHandler.cpp
)
target_include_directories(test_handler PUBLIC ${PUBLIC_INC})

# 실행 파일 (main.cpp 위치에 맞게 경로 조정)
add_executable(server
    ${server_root}/main.cpp
)

# 링크
target_link_libraries(server PRIVATE util server_socket activator test_handler)