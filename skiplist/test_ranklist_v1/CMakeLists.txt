cmake_minimum_required(VERSION 3.6)
project(skiplist_test)

set(ROOT_PATH $ENV{ROOT_PATH})
set(GTEST_LIBDIR ${ROOT_PATH}/googletest/cmake-build-debug/usr/lib/)
set(GTEST_INCDIR ${ROOT_PATH}/googletest/cmake-build-debug/usr/include/)

find_library(GTEST_LIB 
    gtest
    ${GTEST_LIBDIR}
)

find_library(GTEST_MAIN_LIB
    gtest_main
    ${GTEST_LIBDIR}
)

set(GTEST_LIBS ${GTEST_MAIN_LIB} ${GTEST_LIB})

include_directories(${GTEST_INCDIR} ${ROOT_PATH}/skiplist/)

set(CMAKE_CXX_STANDARD 11)
#add_definitions(-std=gnu++11)

add_executable(skiplist_test test.cpp)

target_link_libraries(skiplist_test ${GTEST_LIBS})
