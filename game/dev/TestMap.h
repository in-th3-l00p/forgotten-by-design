#ifndef TESTMAP_H
#define TESTMAP_H

#include "../../engine/domain/Map.h"

namespace game {
    class TestMap final : public engine::domain::Map {
    public:
        TestMap();

        [[nodiscard]] engine::domain::Tile get_tile(std::uint32_t x, std::uint32_t y) const override;
    };
}

#endif //TESTMAP_H
