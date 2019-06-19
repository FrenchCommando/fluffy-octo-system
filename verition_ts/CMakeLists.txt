cmake_minimum_required(VERSION 3.10)
project(verition)

set(CMAKE_CXX_STANDARD 17)

set(VERITION_SOURCE_FILES
        main.cpp
        TimeSeries.h VTime.h)
add_executable(verition ${VERITION_SOURCE_FILES})

# not using googletest, just keep it simple