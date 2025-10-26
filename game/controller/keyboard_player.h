#ifndef KEYBOARD_PLAYER_H
#define KEYBOARD_PLAYER_H

#include <SDL3/SDL_events.h>

#include "../config.h"
#include "../../engine/Window.h"
#include "../../engine/domain/Player.h"

namespace game::controller {
    inline void keyboard_player(engine::domain::Player& player, float& deltaTime) {
        SDL_PumpEvents();
        const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
        auto translate = static_cast<float>(
                keyboard_state[SDL_SCANCODE_W] -
                keyboard_state[SDL_SCANCODE_S]
            ) * config::translate_speed;
        auto rotate = static_cast<float>(
                keyboard_state[SDL_SCANCODE_D] -
                keyboard_state[SDL_SCANCODE_A]
            ) * config::rotate_speed;

        player.dir.rotate(rotate * deltaTime);
        player.pos += translate * deltaTime * player.dir;
    }
}

#endif //KEYBOARD_PLAYER_H
