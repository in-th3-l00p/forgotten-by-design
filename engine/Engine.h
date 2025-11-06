#ifndef ECS_H
#define ECS_H

#include <memory>

#include "engine/Window.h"
#include "engine/scene/Scene.h"

namespace engine {
    class Engine {
        bool running = true;
        Window window;

        std::shared_ptr<Scene> scene;

    public:
        explicit Engine();
        ~Engine() noexcept;

        void set_scene(Scene* scene) noexcept;
        void run();
    };
}

#endif //ECS_H
