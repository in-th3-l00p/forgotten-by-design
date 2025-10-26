#ifndef ECS_H
#define ECS_H

#include <memory>

#include "Window.h"
#include "domain/Scene.h"

namespace engine {
    class Engine {
        bool running = true;
        Window window;

        std::shared_ptr<Scene> scene;

    public:
        explicit Engine();
        ~Engine() noexcept;

        void set_scene(Scene* scene);
        void run() noexcept;
    };
}

#endif //ECS_H
