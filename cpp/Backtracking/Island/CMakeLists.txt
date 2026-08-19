cmake_minimum_required(VERSION 4.2.0)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(Island island.cpp)

target_compile_features(Island PUBLIC cxx_std_23)

