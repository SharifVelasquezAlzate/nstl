cmake_minimum_required(VERSION 3.14)
project(nstl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Declare as library
file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

# Testing
enable_testing()

add_subdirectory(external/googletest)
add_subdirectory(tests)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
