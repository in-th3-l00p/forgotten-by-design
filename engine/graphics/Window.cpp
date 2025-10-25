//
// Created by Tisca Catalin on 26.10.2025.
//

#include "Window.h"

#include <stdexcept>
#include <string>


void Window::initialize() {
    if (!SDL_CreateWindowAndRenderer(
        config::title,
        config::initial_width,
        config::initial_height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL,
        &window,
        &renderer
    )) {
            throw std::runtime_error(std::string("failed to create window and renderer: ") + SDL_GetError());
    }
}

Window::~Window() noexcept {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
