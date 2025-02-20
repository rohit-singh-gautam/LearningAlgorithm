cmake_minimum_required(VERSION 3.16)

project(largestpalindrom)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(largestpalindrom LargestPalindrom.cpp)

target_compile_features(largestpalindrom PUBLIC cxx_std_20)
