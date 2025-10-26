//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef MAP_H
#define MAP_H
#include <cstdint>
#include <optional>

namespace engine {
    namespace domain {

        enum Color {
            WHITE,
            PURPLE
        };

        struct Tile {
            bool empty = false;
            std::optional<Color> color;
        };

        class Map {
            std::uint32_t width;
            std::uint32_t height;

        public:
            Map(
                const std::uint32_t width,
                const std::uint32_t height
            )
                : width(width),
                  height(height) {
            }
            virtual ~Map() = default;

            [[nodiscard]] virtual Tile get_tile(std::uint32_t x, std::uint32_t y) const;
        };

    } // raycasting
}

#endif //MAP_H
