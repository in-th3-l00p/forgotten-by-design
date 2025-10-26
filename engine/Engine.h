#ifndef ECS_H
#define ECS_H

#include "Window.h"

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
