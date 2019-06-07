set(NUMERIC_TEST_FILES
        basic_numeric_test.cpp)
add_executable(runNumericTests ${NUMERIC_TEST_FILES})

target_link_libraries(runNumericTests gtest gtest_main)
target_link_libraries(runNumericTests numeric_tools)

add_test(AllTestsNumeric runNumericTests)