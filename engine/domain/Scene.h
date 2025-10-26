//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "../Window.h"


namespace engine {
    class Scene {
    public:
        Scene();
        virtual ~Scene();

        virtual void update(float deltaTime);
        virtual void render(Window& window) const;
    };
}



#endif //SCENE_H
