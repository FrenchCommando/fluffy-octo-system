cmake_minimum_required(VERSION 3.10)
project(test_main)

set(MAIN_TEST_FILES
        basic_main_test.cpp)
add_executable(runMainTests ${MAIN_TEST_FILES})

target_link_libraries(runMainTests gtest gtest_main)
target_link_libraries(runMainTests sandbox)

add_test(NAME AllTestsMain COMMAND runMainTests)