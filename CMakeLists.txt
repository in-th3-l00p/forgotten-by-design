cmake_minimum_required(VERSION 3.31)
project(forgotten_by_design)

set(CMAKE_CXX_STANDARD 26)
find_package(SDL3 REQUIRED CONFIG)

add_executable(forgotten_by_design main.cpp
        engine/Engine.cpp
        engine/Engine.h
        graphics/Window.cpp
        graphics/Window.h
)
target_link_libraries(forgotten_by_design PRIVATE SDL3::SDL3)