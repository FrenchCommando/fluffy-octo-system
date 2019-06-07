cmake_minimum_required(VERSION 3.10)
project(numeric_tools)

set(CMAKE_CXX_STANDARD 17)

set(NUMERIC_SOURCE_FILES
        numeric_helper.cpp numeric_helper.h)

add_library(numeric_tools ${NUMERIC_SOURCE_FILES})
