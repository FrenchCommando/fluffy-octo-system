cmake_minimum_required(VERSION 3.10)
project(PersoTools)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/numeric_tools)
include_directories(src/parsing_tools)
include_directories(sandbox)
include_directories(palindrome_sandbox)
include_directories(order_exchange)
include_directories(verition_ts)

add_subdirectory(lib/gflags)
add_subdirectory(lib/glog)

add_subdirectory(src/numeric_tools)
add_subdirectory(src/parsing_tools)
add_subdirectory(sandbox)
add_subdirectory(palindrome_sandbox)
add_subdirectory(verition_ts)
add_subdirectory(order_exchange)
add_subdirectory(tests)