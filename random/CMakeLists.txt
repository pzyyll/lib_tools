cmake_minimum_required(VERSION 3.6)
project(random)

set(CMAKE_CXX_STANDARD 11)

add_executable(random main.cpp random_tools.h)
add_executable(random_ok random_ok.cpp random_tools.h)
