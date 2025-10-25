//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef MAP_H
#define MAP_H
#include <cstdint>

namespace raycasting {

enum Color {
    WHITE,
    PURPLE
};

struct Tile {
    Color color;
};

class Map {
    std::uint32_t width;
    std::uint32_t height;

public:
    Map(std::uint32_t width, std::uint32_t height)
        : width(width),
          height(height) {
    }
    virtual ~Map() = default;

    virtual Tile & get_tile(std::uint32_t x, std::uint32_t y) = 0;
};

} // raycasting

#endif //MAP_H
