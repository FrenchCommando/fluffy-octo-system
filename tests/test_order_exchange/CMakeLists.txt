cmake_minimum_required(VERSION 3.10)
project(test_exchange)

set(EXCHANGE_TEST_FILES
        exchange_tests.cpp)
add_executable(runExchangeTests ${EXCHANGE_TEST_FILES})

target_link_libraries(runExchangeTests gtest gtest_main)
target_link_libraries(runExchangeTests order_exchange)

add_test(AllTestsExchange runExchangeTests)