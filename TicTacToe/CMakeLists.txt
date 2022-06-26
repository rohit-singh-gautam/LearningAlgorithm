cmake_minimum_required(VERSION 3.16)

project(tictactoe)

add_executable(tictactoe main.cpp Board.h  Evaluator.h  Intelligence.h  TicTacToeEngine.h)

set_property(TARGET tictactoe PROPERTY CXX_STANDARD 20)

