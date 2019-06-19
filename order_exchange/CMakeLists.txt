cmake_minimum_required(VERSION 3.10)
project(order_exchange)

set(CMAKE_CXX_STANDARD 17)

set(EXCHANGE_SOURCE_FILES
        exchange.cpp exchange.h)
add_library(order_exchange ${EXCHANGE_SOURCE_FILES})
