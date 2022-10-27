include_directories(include)

add_library(game_mode
        src/DetailedGameMode.cpp
        src/FastGameMode.cpp
        src/TournamentGameMode.cpp)

target_include_directories(game_mode PUBLIC include)