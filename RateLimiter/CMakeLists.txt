cmake_minimum_required(VERSION 3.28)

project(RateLimiter)

add_executable(RateLimiter RateLimiter.cpp)

target_compile_features(RateLimiter PUBLIC cxx_std_23)
