cmake_minimum_required(VERSION 3.29)
project(echo)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(echo main.cpp
        echo_application.cpp
        echo_application.h)
