#include "TestMap.h"

namespace game {
    namespace map {
        inline constexpr std::uint32_t width = 8;
        inline constexpr std::uint32_t height = 8;
        inline constexpr int matrix[8][8] = {
            {1, 2, 2, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 2},
            {1, 0, 0, 0, 2, 0, 0, 1},
            {2, 0, 0, 2, 2, 0, 0, 1},
            {2, 0, 0, 2, 0, 0, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 2},
            {1, 1, 2, 2, 1, 1, 2, 2}
        };
    }

    TestMap::TestMap(): Map(map::width, map::height) {}

    engine::domain::Tile TestMap::get_tile(
        const std::uint32_t x,
        const std::uint32_t y
    ) const {
        switch (map::matrix[y][x]) {
            case 0:
                return engine::domain::Tile { {} };
            case 1:
                return engine::domain::Tile {
                    engine::domain::Color::WHITE
                };
            default:
                return engine::domain::Tile {
                    engine::domain::Color::PURPLE
                };
        }
    }
}
