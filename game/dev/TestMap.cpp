#include "game/dev/TestMap.h"

namespace game::dev {
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

    TestMap::TestMap(): engine::entities::Map(map::width, map::height) {}

    engine::entities::Tile TestMap::get_tile(
        const std::uint32_t x,
        const std::uint32_t y
    ) const {
        switch (map::matrix[y][x]) {
            case 0:
                return engine::entities::Tile { {} };
            case 1:
                return engine::entities::Tile {
                    engine::entities::Color::WHITE
                };
            default:
                return engine::entities::Tile {
                    engine::entities::Color::PURPLE
                };
        }
    }
}
