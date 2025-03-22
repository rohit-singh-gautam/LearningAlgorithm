cmake_minimum_required(VERSION 3.16)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(kmax kmax.cpp kmax.h)

target_compile_features(kmax PUBLIC cxx_std_20)
