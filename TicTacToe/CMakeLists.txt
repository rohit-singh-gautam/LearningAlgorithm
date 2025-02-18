cmake_minimum_required(VERSION 3.16)

project(tictactoe)

add_executable(tictactoe main.cpp Board.h  Evaluator.h  Intelligence.h  TicTacToeEngine.h)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override -fanalyzer)
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

target_compile_features(tictactoe PUBLIC cxx_std_23)
