add_executable(BigIntTest main.cpp UnaryOperatorsTest.cpp)

target_link_libraries(BigIntTest PRIVATE BigIntLib gtest)