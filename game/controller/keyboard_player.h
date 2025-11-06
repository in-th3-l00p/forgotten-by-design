#ifndef KEYBOARD_PLAYER_H
#define KEYBOARD_PLAYER_H

#include <SDL3/SDL_events.h>

#include "../config.h"
#include "../../engine/entities/Player.h"

namespace game::controller {
    inline void keyboard_player(
        entity::Player &player,
        const float &delta_time
    ) {
        SDL_PumpEvents();
        const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
        const auto translate = static_cast<float>(
                             keyboard_state[SDL_SCANCODE_W] -
                             keyboard_state[SDL_SCANCODE_S]
                         ) * config::translate_speed;
        const auto rotate = static_cast<float>(
                          keyboard_state[SDL_SCANCODE_D] -
                          keyboard_state[SDL_SCANCODE_A]
                      ) * config::rotate_speed;

        player.dir.rotate(rotate * delta_time);
        player.pos += translate * delta_time * player.dir;
    }
}

#endif //KEYBOARD_PLAYER_H
