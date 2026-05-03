#include "collision/tile_collision.h"

#include <cmath>

namespace pf {

bool TileCollisionMap::load_from_level_collision(const LevelTileCollision& collision) {
    width_ = collision.width;
    height_ = collision.height;
    tile_size_ = collision.tile_size;
    tiles_ = collision.solid;

    return true;
}

bool TileCollisionMap::solid_at(int tile_x, int tile_y) const {
    if (tile_x < 0 || tile_y < 0 || tile_x >= width_ || tile_y >= height_) {
        return true;
    }

    return tiles_[tile_y * width_ + tile_x] != 0;
}

bool TileCollisionMap::solid_at_world(float world_x, float world_y) const {
    const int tile_x = static_cast<int>(std::floor(world_x / tile_size_));
    const int tile_y = static_cast<int>(std::floor(world_y / tile_size_));

    return solid_at(tile_x, tile_y);
}

Aabb TileCollisionMap::tile_bounds(int tile_x, int tile_y) const {
    return Aabb {
        static_cast<float>(tile_x * tile_size_),
        static_cast<float>(tile_y * tile_size_),
        static_cast<float>(tile_size_),
        static_cast<float>(tile_size_)
    };
}

}
