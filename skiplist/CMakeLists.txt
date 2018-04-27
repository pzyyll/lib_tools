cmake_minimum_required(VERSION 3.6)
project(skiplist)

set(CMAKE_CXX_STANDARD 11)

if (CHECK_MALLOC)
    add_definitions(-DCHECK_MALLOC)
endif (CHECK_MALLOC)

add_executable(skiplist main.cpp skiplist.h ranklist_v1.h)
add_executable(ranklist_v1_test ranklist_v1_test.cpp)
