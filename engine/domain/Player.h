#ifndef PLAYER_H
#define PLAYER_H

#include "../../utils/math.h"

namespace engine::domain {
    struct Player {
        math::vec2 pos, dir;
        float radius;
    };
} // raycasting

#endif //PLAYER_H
