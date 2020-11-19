cmake_minimum_required(VERSION 3.17)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CALC_SRC Calculator_src/*.cpp Calculator_src/*.h)

add_executable(Calculator ${CALC_SRC})

add_library(Pow SHARED dll_src/Pow.cpp)
add_library(SIN SHARED  dll_src/SIN.cpp)
add_library(Division SHARED  dll_src/Division.cpp)
add_library(Subtraction SHARED  dll_src/Subtraction.cpp)
