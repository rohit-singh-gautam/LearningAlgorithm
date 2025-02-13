cmake_minimum_required(VERSION 3.28)

project(MinSlidingWindow)

add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) # -fanalyzer

add_executable(MinSlidingWindow MinSlidingWindow.cpp)

target_compile_features(MinSlidingWindow PRIVATE cxx_std_23)

