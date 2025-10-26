//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef ECS_H
#define ECS_H

#include "Window.h"
#include "raycasting/Renderer.h"
#include <memory>

namespace engine {
    class Engine {
        bool running = true;
        Window window;

    public:
        Engine();
        ~Engine() noexcept;

        void run() noexcept;
    };
}

#endif //ECS_H
