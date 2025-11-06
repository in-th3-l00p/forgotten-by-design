#ifndef SCENE_H
#define SCENE_H
#include "engine/Window.h"

namespace engine::scene {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void update(float &delta_time) {}
        virtual void ui() {}
        virtual void render(Window& window) const {}
    };
}

#endif //SCENE_H
