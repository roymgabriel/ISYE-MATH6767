cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp bond.cpp bond.h derivative.cpp derivative.h)
