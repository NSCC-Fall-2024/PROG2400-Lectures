cmake_minimum_required(VERSION 3.29)
project(command_line)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(command_line main.cpp)
