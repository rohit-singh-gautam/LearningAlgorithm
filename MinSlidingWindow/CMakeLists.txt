cmake_minimum_required(VERSION 3.28)

project(MinSlidingWindow)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) #-fanalyzer
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(MinSlidingWindow MinSlidingWindow.cpp)

target_compile_features(MinSlidingWindow PRIVATE cxx_std_23)

