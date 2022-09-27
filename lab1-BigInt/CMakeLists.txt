cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME BigInt)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARY_DIR lib )
set(LIBRARY bigint googletest)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARY})
	add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
	message(STATUS "Add subdirectory ${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARY})