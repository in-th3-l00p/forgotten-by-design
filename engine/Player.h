#ifndef PLAYER_H
#define PLAYER_H

#include "../utils/math.h"

namespace engine {
    struct Player {
        math::vec2 pos, dir;
        float radius;
    };
}

#endif //PLAYER_H
