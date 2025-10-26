//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "../domain/Map.h"
#include "../domain/Player.h"
#include "../Window.h"

namespace engine {
    namespace raycasting {

        class Renderer {
            const domain::Map& map;
            const domain::Player& player;

        public:
            Renderer(const domain::Map &map, const domain::Player &player)
                : map(map),
                  player(player) {
            }

            void render(Window &window) const;
        };

    } // raycasting
}

#endif //RENDERER_H
