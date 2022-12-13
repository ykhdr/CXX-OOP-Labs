project(${PROJECT_NAME} CXX)

include_directories(include)

add_library(tuplePrint INTERFACE)

target_include_directories(tuplePrint INTERFACE include)