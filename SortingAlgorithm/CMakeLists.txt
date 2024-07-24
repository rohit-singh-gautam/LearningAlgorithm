cmake_minimum_required(VERSION 3.16)

project(SortingAlgorithm)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(SortingAlgorithm
    DisplayHelper.cpp
    SortingAlgorithm.cpp
    TestHelper.cpp
)

set_property(TARGET SortingAlgorithm PROPERTY CXX_STANDARD 23)
