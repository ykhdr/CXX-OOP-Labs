add_library(BigIntLib BigInt.cpp)

target_include_directories(BigIntLib PUBLIC include)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE BigIntLib)