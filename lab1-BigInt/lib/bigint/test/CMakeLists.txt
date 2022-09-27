set(TEST_PROJECT_NAME bigint_tests)
set(LIBRARY_TESTS_SOURCE test_bigint.cpp)

project(${TEST_PROJECT_NAME} CXX)

enable_testing()

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})

target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main ${LIBRARY_NAME} )

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})