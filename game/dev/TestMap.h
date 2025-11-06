#ifndef TESTMAP_H
#define TESTMAP_H

#include "../../engine/entities/Map.h"

namespace game::dev {
    class TestMap final : public engine::entities::Map {
    public:
        TestMap();

        [[nodiscard]] engine::entities::Tile get_tile(std::uint32_t x, std::uint32_t y) const override;
    };
}

#endif //TESTMAP_H
