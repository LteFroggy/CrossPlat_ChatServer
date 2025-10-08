cmake_minimum_required(VERSION 3.20)  # CMake 최소버전 명시
project(hello LANGUAGES CXX)          # 프로젝트 이름, 사용하는 언어 명시

set(CMAKE_CXX_STANDARD 17)            # 이 프로젝트의 모든 타깃은 C++17 사용
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # C++17이 지원 안되면, 빌드 안하기

add_subdirectory(src)                 # src라는 폴더 안에도 CMakeLists.txt가 있으니, 그 설정 포함하기