//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "Map.h"
#include "Player.h"
#include "../Window.h"

namespace engine {
    namespace raycasting {

        class Renderer {
            Map& map;
            Player& player;

        public:
            Renderer(Map &map, Player &player)
                : map(map),
                  player(player) {
            }

            void render(Window &window);
        };

    } // raycasting
}

#endif //RENDERER_H
