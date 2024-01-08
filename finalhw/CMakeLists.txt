cmake_minimum_required(VERSION 3.27)
project(poly_sort)

set(CMAKE_CXX_STANDARD 23)

add_executable(poly_sort main.cpp
        poly_table.cpp
        poly_table.h
        sorter.cpp
        sorter.h)
