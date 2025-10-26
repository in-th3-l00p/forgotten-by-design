#ifndef GAME_H
#define GAME_H

#include "../engine/Engine.h"

namespace game {
    inline void run() {
        auto engine = engine::Engine();
        engine.run();
    }
}

#endif //GAME_H
