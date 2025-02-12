cmake_minimum_required(VERSION 3.16)

# Project name
project(SplitOrderedMap)

# Add source files
set(SOURCES
    SplitOrderedMap.cpp
)

# Create executable
add_executable(SplitOrderedMap ${SOURCES})

target_compile_features(SplitOrderedMap PRIVATE cxx_std_23)
