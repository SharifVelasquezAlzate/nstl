cmake_minimum_required(VERSION 3.14)
project(nstl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing
enable_testing()

add_subdirectory(external/googletest)

# 
