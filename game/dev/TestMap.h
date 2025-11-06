#ifndef TESTMAP_H
#define TESTMAP_H

#include "serialization/Map.h"

namespace game {
    class TestMap final : public engine::Map {
    public:
        TestMap();

        [[nodiscard]] engine::Tile get_tile(std::uint32_t x, std::uint32_t y) const override;
    };
}

#endif //TESTMAP_H
