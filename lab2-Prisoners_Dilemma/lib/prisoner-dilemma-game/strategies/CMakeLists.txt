
include_directories(str_dir include)

add_library(strategies include/SimpleStrategy.h src/SimpleStrategy.cpp include/DefaultStrategy.h src/DefaultStrategy.cpp include/RandomStrategy.h src/RandomStrategy.cpp)

target_include_directories(strategies PUBLIC include)

#target_link_libraries(strategies PUBLIC str_dir)

link_libraries(${LIBRARY_NAME} PUBLIC strategies)