cmake_minimum_required(VERSION 3.10)
project(tests)

enable_testing()
add_subdirectory(libs/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(test_numeric)
add_subdirectory(test_order_exchange)
add_subdirectory(test_main)