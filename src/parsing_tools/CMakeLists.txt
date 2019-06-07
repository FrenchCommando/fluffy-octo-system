cmake_minimum_required(VERSION 3.10)
project(parsing_tools)

set(CMAKE_CXX_STANDARD 17)

set(PARSING_SOURCE_FILES
        input_parser.cpp input_parser.h)

add_library(parsing_tools ${PARSING_SOURCE_FILES})
