cmake_minimum_required(VERSION 3.16)

project(wildcard)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(wildcard WildcardSearch.cpp)

target_compile_features(wildcard PUBLIC cxx_std_20)
