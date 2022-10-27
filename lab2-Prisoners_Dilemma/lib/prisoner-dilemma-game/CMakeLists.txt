project(${PROJECT_NAME} CXX)

include_directories(include)

add_library(game_engine STATIC
        include/Game.h src/Game.cpp
        src/MoveMatrix.cpp src/Player.cpp
        src/PlayingField.cpp src/ResultMatrix.cpp
        src/Factory.cpp include/Factory.h
        src/ParsingCommandLineArgs.cpp include/ParsingCommandLineArgs.h)

target_include_directories(game_engine PUBLIC include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${PROJECT_NAME} game_engine strategies game_mode)

add_subdirectory(strategies)
add_subdirectory(game-mode)