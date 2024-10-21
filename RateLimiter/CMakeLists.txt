cmake_minimum_required(VERSION 3.28)

project(RateLimiter)

add_executable(RateLimiter RateLimiter.cpp)

set_property(TARGET RateLimiter PROPERTY CXX_STANDARD 23)
