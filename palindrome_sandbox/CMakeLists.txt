cmake_minimum_required(VERSION 3.10)
project(palindrome)

set(CMAKE_CXX_STANDARD 17)

set(PALINDROME_SOURCE_FILES
        main.cpp palindrome.h palindrome.cpp palindrome_substring.cpp palindrome_substring.h arthur.cpp arthur.h suffix_tree.cpp suffix_tree.h)
add_executable(palindrome ${PALINDROME_SOURCE_FILES})

set_target_properties(palindrome PROPERTIES ENABLE_EXPORTS 1)

target_link_libraries(palindrome
        glog::glog)
