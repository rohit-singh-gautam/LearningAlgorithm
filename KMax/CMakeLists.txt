cmake_minimum_required(VERSION 3.16)

project(kmax)

add_executable(kmax kmax.cpp kmax.h)

set_property(TARGET kmax PROPERTY CXX_STANDARD 23)
