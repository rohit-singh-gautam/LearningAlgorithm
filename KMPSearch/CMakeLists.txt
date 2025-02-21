cmake_minimum_required(VERSION 3.6)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) # -fanalyzer
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

project(KMPSearch)

add_executable(KMPSearch KMPSearch.cpp)

target_compile_features(KMPSearch PUBLIC cxx_std_20)
