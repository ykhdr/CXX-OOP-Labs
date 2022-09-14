cmake_minimum_required(VERSION 3.10)

project(BigInt)

set(CMAKE_CXX_STANDARD 14)

add_library(BigIntLib BigInt.h BigInt.cpp)

add_executable(main main.cpp)

target_link_libraries(main BigIntLib)
