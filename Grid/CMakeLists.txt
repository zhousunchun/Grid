cmake_minimum_required(VERSION 2.6)
project(grid)

add_executable(grid main.cpp)

install(TARGETS grid RUNTIME DESTINATION bin)
