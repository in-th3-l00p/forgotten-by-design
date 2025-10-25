//
// Created by Tisca Catalin on 26.10.2025.
//

#include "Engine.h"

#include <print>
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>

Engine::Engine() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(std::string{"SDL_Init failed: "} + SDL_GetError());
    }
}

Engine::~Engine() noexcept {
    SDL_Quit();
}

void Engine::run() noexcept {
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            SDL_QUIT:
                running = false;
                break;
            default:
                std::print("unhandled event type: {}\n", event.type);
            }
        }
    }
}