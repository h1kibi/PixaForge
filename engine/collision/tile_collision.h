#pragma once

#include <array>

#include "collision/aabb.h"

namespace pf {

class TileCollisionMap {
public:
    static constexpr int width = 20;
    static constexpr int height = 12;
    static constexpr int tile_size = 16;

    bool solid_at(int tile_x, int tile_y) const;
    bool solid_at_world(float world_x, float world_y) const;

    Aabb tile_bounds(int tile_x, int tile_y) const;

private:
    std::array<int, width * height> tiles_ = {
        // 20 x 12
        // 0 = empty, 1 = solid

        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
        1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };
};

}
