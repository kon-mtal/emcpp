cmake_minimum_required(VERSION 4.1)
project(01_copy_and_move)

set(CMAKE_CXX_STANDARD 20)

add_executable(01_copy_and_move main.cpp
        Matrix.cpp
        Matrix.h)
