cmake_minimum_required(VERSION 3.16)

project(kmax)

add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)

add_executable(kmax kmax.cpp kmax.h)

target_compile_features(kmax PUBLIC cxx_std_23)
