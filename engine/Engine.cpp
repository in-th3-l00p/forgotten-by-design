//
// Created by Tisca Catalin on 26.10.2025.
//

#include "Engine.h"

#include <print>
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>

#include "../utils/Logging.h"

Engine::Engine() {
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(std::string{"SDL_Init failed: "} + SDL_GetError());
    logging::info("sdl3 initialized successfully");
    window.initialize();
}

Engine::~Engine() noexcept {
    SDL_Quit();
}

void Engine::run() noexcept {
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    logging::info("sdl3 event quit triggered");
                    running = false;
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(window.renderer1(), 0, 0, 0, 255);
        SDL_RenderClear(window.renderer1());

        SDL_RenderPresent(window.renderer1());
    }
}