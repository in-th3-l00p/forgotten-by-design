#ifndef MAP_H
#define MAP_H

#include <optional>

namespace engine::entities {
    enum Color {
        WHITE,
        PURPLE
    };

    struct Tile {
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

        [[nodiscard]] virtual Tile get_tile(std::uint32_t x, std::uint32_t y) const = 0;
        [[nodiscard]] std::uint32_t get_width() const {
            return width;
        }
        [[nodiscard]] std::uint32_t get_height() const {
            return height;
        }
    };

} // entities

#endif //MAP_H
