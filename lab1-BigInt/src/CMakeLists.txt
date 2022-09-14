add_executable(BigInt main.cpp)

add_library(BigIntLib BigInt.h BigInt.cpp)

target_link_libraries(BigInt PRIVATE BigIntLib)
