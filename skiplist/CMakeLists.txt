cmake_minimum_required(VERSION 3.9)
project(skiplist)

set(CMAKE_CXX_STANDARD 11)

add_executable(skiplist main.cpp skiplist.h ranklist_v1.h)
add_executable(ranklist_v1_test ranklist_v1_test.cpp)