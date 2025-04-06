cmake_minimum_required(VERSION 3.28)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(Deque Deque.cpp)

target_compile_features(Deque PRIVATE cxx_std_20)
