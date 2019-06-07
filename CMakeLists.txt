cmake_minimum_required(VERSION 3.10)
project(PersoTools)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/numeric_tools)
include_directories(src/parsing_tools)
include_directories(sandbox)

add_subdirectory(src/numeric_tools)
add_subdirectory(src/parsing_tools)
add_subdirectory(sandbox)

add_subdirectory(tests)