#include "Engine.h"

#include <print>
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>

#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "../utils/logging.h"

namespace engine {
    Engine::Engine() {
        if (!SDL_Init(SDL_INIT_VIDEO))
            throw std::runtime_error(std::string{"SDL_Init failed: "} + SDL_GetError());
        logging::info("sdl3 initialized successfully");
        window.initialize();

        // initializing imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL3_InitForSDLRenderer(window.window1(), window.renderer1());
        ImGui_ImplSDLRenderer3_Init(window.renderer1());

        logging::info("imgui initialized successfully");
    }

    Engine::~Engine() noexcept {
        SDL_Quit();
    }

    void Engine::set_scene(Scene* scene) noexcept {
        this->scene = std::shared_ptr<Scene>(scene);
    }

    void Engine::run() {
        if (scene == nullptr)
            throw std::runtime_error("engine cannot run when scene is null, call engine::set_scene first");

        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL3_ProcessEvent(&event);
                switch (event.type) {
                    case SDL_EVENT_QUIT:
                        logging::info("sdl3 event quit triggered");
                        running = false;
                        break;
                    default:
                        break;
                }
            }

            scene->update(0);

            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            scene->ui();
            ImGui::Render();

            SDL_SetRenderDrawColor(window.renderer1(), 0, 0, 0, 255);
            SDL_RenderClear(window.renderer1());

            scene->render(window);

            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), window.renderer1());
            SDL_RenderPresent(window.renderer1());
        }
    }
}
