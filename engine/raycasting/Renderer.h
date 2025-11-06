#ifndef RENDERER_H
#define RENDERER_H
#include "serialization/Map.h"
#include "engine/entities/Player.h"
#include "engine/Window.h"

namespace engine::raycasting {
    using entity::Player;

    class Renderer {
        const Map& map;
        const Player& player;

    public:
        Renderer(const Map &map, const Player &player)
            : map(map),
              player(player) {
        }

        void render(Window &window) const;
    };

} // raycasting

#endif //RENDERER_H
