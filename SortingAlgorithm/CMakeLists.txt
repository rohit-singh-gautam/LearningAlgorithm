cmake_minimum_required(VERSION 3.16)

project(SortingAlgorithm)

add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -fanalyzer)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(SortingAlgorithm
    DisplayHelper.cpp
    SortingAlgorithm.cpp
    AllSortInitialization.cpp
)

set_property(TARGET SortingAlgorithm PROPERTY CXX_STANDARD 23)
