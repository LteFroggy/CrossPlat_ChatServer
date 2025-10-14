# util 폴더 안의 cpp 파일로 util 라이브러리 생성
add_library(util
    util/NumberUtil.cpp
)

# 헤더를 include 가능하게 공개
target_include_directories(util PUBLIC util)

# main.cpp를 실행파일로 빌드
add_executable(hello main.cpp)

# main에서 util 사용 가능하도록 링크
target_link_libraries(hello PRIVATE util)