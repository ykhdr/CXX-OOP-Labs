set(LIBRARY_NAME game_lib)
set(LIBRARY_HEADERS_DIR include)

project(${PROJECT_NAME} CXX)

add_library(${LIBRARY_NAME} STATIC include/Game.h src/Game.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})