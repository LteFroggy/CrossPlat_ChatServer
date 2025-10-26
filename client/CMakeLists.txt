cmake_minimum_required(VERSION 3.20)
project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 공용 헤더 경로 공개
set(PUBLIC_INC ${CMAKE_SOURCE_DIR}/include)

# socket 경로 주기
add_library(socket
    ${CMAKE_SOURCE_DIR}/src/socket/MacClientSocket.cpp
)
target_include_directories(socket PUBLIC PUBLIC_INC)

add_executable(main,
    ${CMAKE_SOURCE_DIR}/main.cpp
)