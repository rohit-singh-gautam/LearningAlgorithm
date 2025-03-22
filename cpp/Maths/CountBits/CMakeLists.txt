cmake_minimum_required(VERSION 3.16)

add_executable(CountBits CountBits.cpp)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

target_compile_features(CountBits PUBLIC cxx_std_20)
