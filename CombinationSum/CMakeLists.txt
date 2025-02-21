cmake_minimum_required(VERSION 3.16)

project(CombinationSum)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(CombinationSum CombinationSum.cpp)

target_compile_features(CombinationSum PUBLIC cxx_std_20)

