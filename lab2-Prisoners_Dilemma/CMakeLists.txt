cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME lab2-Prisoners_Dilemma)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(lib/prisoner-dilemma-game)