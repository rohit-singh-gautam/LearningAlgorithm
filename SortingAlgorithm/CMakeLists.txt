cmake_minimum_required(VERSION 3.28)

project(SortingAlgorithm)

add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -fanalyzer)

add_executable(SortingAlgorithm
    DisplayHelper.cpp
    SortingAlgorithm.cpp
    AllSortInitialization.cpp
)

set_property(TARGET SortingAlgorithm PROPERTY CXX_STANDARD 26)
