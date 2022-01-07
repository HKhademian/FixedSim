cmake_minimum_required(VERSION 3.19)
project(project
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test-fixed
        fixed.hpp test-fixed.cpp)

add_executable(test-mask
        fixed.hpp test-mask.cpp)
