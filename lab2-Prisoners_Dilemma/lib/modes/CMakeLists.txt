include_directories(include)

add_library(modes
        src/DetailedGameMode.cpp
        src/FastGameMode.cpp
        src/TournamentGameMode.cpp)

target_include_directories(modes PUBLIC include)