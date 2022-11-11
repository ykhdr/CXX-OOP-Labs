include_directories(include)

add_library(strategies
        src/SimpleStrategy.cpp
        src/DefaultStrategy.cpp
        src/RandomStrategy.cpp
        src/SmartStrategy.cpp
        src/StrategyFactory.cpp
        src/PersonStrategy.cpp
        )

target_include_directories(strategies PUBLIC include)