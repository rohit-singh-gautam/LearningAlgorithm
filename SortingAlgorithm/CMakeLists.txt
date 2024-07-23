cmake_minimum_required(VERSION 3.16)

project(SortingAlgorithm)

add_executable(SortingAlgorithm
    DisplayHelper.cpp
    SortingAlgorithm.cpp
    TestHelper.cpp
)

set_property(TARGET SortingAlgorithm PROPERTY CXX_STANDARD 20)
