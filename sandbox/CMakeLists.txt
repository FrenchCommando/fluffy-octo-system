cmake_minimum_required(VERSION 3.10)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SANDBOX_SOURCE_FILES
        main.cpp
        sample_file.cpp other_sample_file.cpp loop.cpp)
add_executable(sandbox ${SANDBOX_SOURCE_FILES})

set_target_properties(sandbox PROPERTIES ENABLE_EXPORTS 1)

target_link_libraries(sandbox
        parsing_tools numeric_tools glog::glog)
