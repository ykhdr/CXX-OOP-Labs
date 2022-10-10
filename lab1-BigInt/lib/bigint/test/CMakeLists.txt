set(TEST_PROJECT_NAME bigint_tests)
set(LIBRARY_TESTS_SOURCE test_bigint.cpp ../src/bigint.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

add_custom_target(gcov
    COMMAND mkdir -p gcoverage
    #COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    #COMMAND gcov -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR}
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/lib/bigint/src/*.cpp
    COMMAND echo "-- Source diretorie: ${CMAKE_SOURCE_DIR}/src/"
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
    )

add_dependencies(gcov bigint_tests)

project(${TEST_PROJECT_NAME} CXX)

enable_testing()

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})

target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main ${LIBRARY_NAME} )

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})
