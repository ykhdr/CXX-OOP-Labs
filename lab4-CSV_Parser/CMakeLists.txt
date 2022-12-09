cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME lab4-CSVParser)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(lib/tuplePrint)
add_subdirectory(lib/CSVParser)

target_link_libraries(${PROJECT_NAME} CSVParser)