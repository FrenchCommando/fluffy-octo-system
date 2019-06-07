cmake_minimum_required(VERSION 3.10)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SANDBOX_SOURCE_FILES main.cpp)
add_executable(sandbox ${SANDBOX_SOURCE_FILES})

target_link_libraries(sandbox
        parsing_tools numeric_tools)