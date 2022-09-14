project(BigInt)

add_executable(main main.cpp)

add_library(BigIntLib BigInt.h BigInt.cpp)

target_link_libraries(main PRIVATE BigIntLib)
