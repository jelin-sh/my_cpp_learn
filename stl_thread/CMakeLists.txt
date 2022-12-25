cmake_minimum_required(VERSION 3.16)
project(stl_thread)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
include(CMakeTools.cmake)
include(AddGTest.cmake)

enable_testing()
add_executable(stl_thread main.cpp src/test_thread.cpp)
target_link_libraries(stl_thread Threads::Threads GTest::gtest_main)


