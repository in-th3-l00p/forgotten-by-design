#ifndef SCENE_H
#define SCENE_H
#include "../Window.h"

namespace engine {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void update(float deltaTime) {}
        virtual void render(Window& window) const {}
    };
}

#endif //SCENE_H
