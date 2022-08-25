cmake_minimum_required(VERSION 3.21)
project(AP_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(AP_3 main.cpp dijkstra.cpp dijkstra.h catch.hpp)
add_executable(AP_3_test Unit_testing.cpp dijkstra.cpp dijkstra.h catch.hpp)
