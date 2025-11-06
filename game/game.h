#ifndef GAME_H
#define GAME_H

#include "engine/Engine.h"
#include "game/dev/RaycasterTestScene.h"

namespace game {
    inline void run() {
        auto engine = engine::Engine();
        engine.set_scene(new dev::RaycasterTestScene());
        engine.run();
    }
}

#endif //GAME_H
