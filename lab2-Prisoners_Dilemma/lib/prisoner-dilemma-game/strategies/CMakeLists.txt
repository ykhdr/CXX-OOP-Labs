
include_directories(str_dir include)

add_library(strategies include/SimpleStrategy.h src/SimpleStrategy.cpp)

target_link_libraries(strategies PUBLIC str_dir)

link_libraries(${LIBRARY_NAME} strategies)