cmake_minimum_required(VERSION 3.10)

project(BigInt)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(test)
