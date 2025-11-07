#include "TextureStore.h"
#include "utils/logging.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_surface.h>

namespace engine::serialization {
    void TextureStore::load_texture(
        const std::uint32_t id,
        const char* path
    ) {
        const auto surface = IMG_Load(path);
        if (surface == nullptr)
            throw std::runtime_error("failed to load texture: " + std::string(path) + "; error: " + SDL_GetError());
        auto texture = std::vector(surface->h, std::vector<std::uint32_t>(surface->w));
        for (int y = 0; y < surface->h; y++) {
            const auto row = static_cast<std::uint32_t *>(surface->pixels) + y * surface->pitch;
            for (int x = 0; x < surface->w; x++)
                texture[y][x] = row[x];
        }

        store.insert({id, texture});
        logging::info("texture {} was loaded and stored at id={}", path, id);
        SDL_DestroySurface(surface);
    }

    texture TextureStore::get_texture(const std::uint32_t id) const {
        return store.at(id);
    }

    void TextureStore::remove_texture(const std::uint32_t id) {
        logging::info("texture {} removed", id);
        store.erase(id);
    }
}

