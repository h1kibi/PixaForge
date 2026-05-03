#pragma once

#include <vector>

#include "collision/aabb.h"
#include "level/level_data.h"

namespace pf {

class TileCollisionMap {
public:
    bool load_from_level_collision(const LevelTileCollision& collision);

    bool solid_at(int tile_x, int tile_y) const;
    bool solid_at_world(float world_x, float world_y) const;

    Aabb tile_bounds(int tile_x, int tile_y) const;

    int width() const { return width_; }
    int height() const { return height_; }
    int tile_size() const { return tile_size_; }

private:
    int width_ = 0;
    int height_ = 0;
    int tile_size_ = 16;
    std::vector<int> tiles_;
};

}
