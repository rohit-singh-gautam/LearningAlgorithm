cmake_minimum_required(VERSION 3.16)

project(StringMultiply)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) # -fanalyzer
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(StringMultiply StringMultiply.cpp)

target_compile_features(StringMultiply PUBLIC cxx_std_20)

