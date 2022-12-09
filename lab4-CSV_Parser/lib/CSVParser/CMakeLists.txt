project(${PROJECT_NAME} CXX)

include_directories(include)

add_library(CSVParser STATIC
        src/CSVParser.cpp)

target_include_directories(CSVParser PUBLIC include)

target_link_libraries(CSVParser tuplePrint)