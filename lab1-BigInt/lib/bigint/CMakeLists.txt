set(LIBRARY_NAME bigint_lib)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS ${LIBRARY_HEADERS_DIR}/bigint.h)
set(LIBRARY_SOURCE_DIR src)
set(LIBRARY_SOURCE ${LIBRARY_SOURCE_DIR}/bigint.cpp)

project(${PROJECT_NAME} CXX)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})

add_subdirectory(test)