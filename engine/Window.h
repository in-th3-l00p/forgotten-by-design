#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>

namespace engine {
    namespace config {
        static const char* title = "forgotten by design";
        static constexpr int initial_width = 1280;
        static constexpr int initial_height = 720;
    }

    class Window {
        SDL_Window* window{};
        SDL_Renderer* renderer{};

    public:
        void initialize();
        ~Window() noexcept;

        [[nodiscard]] SDL_Window *& window1() {
            return window;
        }

        [[nodiscard]] SDL_Renderer *& renderer1() {
            return renderer;
        }
    };
}

#endif //WINDOW_H
