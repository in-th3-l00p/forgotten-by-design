cmake_minimum_required(VERSION 3.31)
project(forgotten_by_design)

set(CMAKE_CXX_STANDARD 26)
find_package(SDL3 REQUIRED CONFIG)

add_executable(forgotten_by_design main.cpp
        engine/Engine.cpp
        engine/Engine.h
        engine/Window.cpp
        engine/Window.h
        utils/Logging.h
        engine/raycasting/Renderer.cpp
        engine/raycasting/Renderer.h
        engine/domain/Map.h
        engine/domain/Player.h
        engine/domain/Scene.h
        game/game.h
        game/dev/RaycasterTestScene.cpp
        game/dev/RaycasterTestScene.h
        game/dev/TestMap.cpp
        game/dev/TestMap.h
)
target_link_libraries(forgotten_by_design PRIVATE SDL3::SDL3)