#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <unordered_map>
#include <vector>

namespace engine::serialization {
    using texture = std::vector<std::vector<std::uint32_t> >;

    class TextureStore {
        // textures are map by ids
        std::unordered_map<std::uint32_t, texture> store;

    public:
        TextureStore() = default;

        void load_texture(
            std::uint32_t id,
            const char *path
        );

        [[nodiscard]] texture get_texture(std::uint32_t id) const;

        void remove_texture(std::uint32_t id);
    };
} // serialization

#endif //TEXTURELOADER_H
