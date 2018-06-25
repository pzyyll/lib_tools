cmake_minimum_required(VERSION 3.6)
project(random)

set(CMAKE_CXX_STANDARD 11)

add_executable(random main.cpp random_tools.h random_tools.cpp)
add_executable(random_ok random_ok.cpp random_tools.h random_tools.cpp)
add_executable(random_1_2 test_random1_2.cpp random_1.cpp random_2.cpp random_tools.cpp)
