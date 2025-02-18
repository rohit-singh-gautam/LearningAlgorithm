cmake_minimum_required(VERSION 3.28)

project(SortingAlgorithm)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(SortingAlgorithm
    DisplayHelper.cpp
    SortingAlgorithm.cpp
    AllSortInitialization.cpp
    Priority.cpp
)

target_compile_features(SortingAlgorithm PRIVATE cxx_std_23)
