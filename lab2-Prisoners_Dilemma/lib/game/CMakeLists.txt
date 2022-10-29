project(${PROJECT_NAME} CXX)

include_directories(include)

add_library(game_engine STATIC
        src/Game.cpp
        )

target_include_directories(game_engine PUBLIC include)
target_link_libraries(game_engine PUBLIC strategies modes matrix_field)