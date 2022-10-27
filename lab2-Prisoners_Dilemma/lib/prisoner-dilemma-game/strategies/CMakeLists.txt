include_directories(include)

add_library(strategies
        src/SimpleStrategy.cpp
        src/DefaultStrategy.cpp
        src/RandomStrategy.cpp)

target_include_directories(strategies PUBLIC include)