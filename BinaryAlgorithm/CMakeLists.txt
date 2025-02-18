cmake_minimum_required(VERSION 3.16)

project(BinaryAlgorithm)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) # -fanalyzer
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(BinaryAlgorithm BinaryAlgorithm.cpp)

set_property(TARGET BinaryAlgorithm PROPERTY CXX_STANDARD 20)

