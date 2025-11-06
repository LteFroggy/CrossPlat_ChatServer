# 공용 헤더 경로 공개
set(client_root ${CMAKE_SOURCE_DIR}/client)
set(PUBLIC_INC ${client_root}/include)

# client_socket이란 이름으로 MacClientSocket.cpp 컴파일해두기
add_library(client_socket
    ${client_root}/src/socket/MacClientSocketMaker.cpp
)
# client_socket이 import할 때 경로 알 수 있도록 PUBLIC_INC 주기, PUBLIC이니 client도 이걸 링크받으면서 PUBLIC_INC에서 이 import가 가능함을 알 수 있음.
target_include_directories(client_socket PUBLIC ${PUBLIC_INC})

add_executable(client
    ${client_root}/main.cpp
)

target_link_libraries(client PUBLIC client_socket)