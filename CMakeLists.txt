cmake_minimum_required(VERSION 3.31)
project(forgotten_by_design)

set(CMAKE_CXX_STANDARD 26)
find_package(SDL3 REQUIRED CONFIG)

# defining "imgui"
add_library(imgui
        vendor/imgui/imconfig.h
        vendor/imgui/imgui.h
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_internal.h
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h
        vendor/imgui/imstb_truetype.h
        vendor/imgui/backend/imgui_impl_sdl3.h
        vendor/imgui/backend/imgui_impl_sdl3.cpp
        vendor/imgui/backend/imgui_impl_sdlrenderer3.h
        vendor/imgui/backend/imgui_impl_sdlrenderer3.cpp
)
target_link_libraries(imgui PRIVATE SDL3::SDL3)
target_include_directories(imgui PUBLIC
        vendor/imgui
        vendor/imgui/backend
)

# defining the executable
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
        utils/math.h
        game/controller/keyboard_player.h
        game/config.h
)

target_link_libraries(forgotten_by_design PRIVATE SDL3::SDL3)
target_link_libraries(forgotten_by_design PRIVATE imgui)
