cmake_minimum_required(VERSION 3.26)
project(slovnik)

set(CMAKE_CXX_STANDARD 17)

add_executable(slovnik main.cpp
        operations.h
        operations.cpp)
