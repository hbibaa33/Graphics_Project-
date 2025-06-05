cmake_minimum_required(VERSION 3.30)
project(Graphlics_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graphlics_project main.cpp
        src/painter/Painter.cpp
        src/painter/Painter.h)
