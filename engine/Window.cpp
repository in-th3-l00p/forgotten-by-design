#include "engine/Window.h"

#include <stdexcept>
#include <string>

#include "utils/logging.h"

namespace engine {
    void Window::initialize() {
        if (!SDL_CreateWindowAndRenderer(
            config::title,
            config::initial_width,
            config::initial_height,
            SDL_WINDOW_RESIZABLE,
            &window,
            &renderer
        ))
            throw std::runtime_error(std::string("failed to create window and renderer: ") + SDL_GetError());
        logging::info("window initialized successfully");
    }

    Window::~Window() noexcept {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
}
