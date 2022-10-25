set(LIBRARY_NAME game_lib)
set(LIBRARY_HEADERS_DIR include)

project(${PROJECT_NAME} CXX)

include_directories(LIBRARY_HEADERS_DIR include )

add_library(${LIBRARY_NAME} STATIC include/Game.h src/Game.cpp
        src/MoveMatrix.cpp src/Player.cpp src/PlayingField.cpp src/ResultMatrix.cpp
        strategies/include/SimpleStrategy.h strategies/src/SimpleStrategy.cpp
        strategies/include/DefaultStrategy.h strategies/src/DefaultStrategy.cpp
        strategies/include/RandomStrategy.h strategies/src/RandomStrategy.cpp
        src/Factory.cpp include/Factory.h src/ParsingCommandLineArgs.cpp include/ParsingCommandLineArgs.h)

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

add_subdirectory(strategies)