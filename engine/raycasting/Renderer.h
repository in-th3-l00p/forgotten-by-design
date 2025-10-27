#ifndef RENDERER_H
#define RENDERER_H
#include "../Map.h"
#include "../Player.h"
#include "../Window.h"

namespace engine::raycasting {

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
