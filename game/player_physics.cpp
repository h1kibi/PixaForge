#include "player_physics.h"

#include <algorithm>
#include <cmath>

namespace {

bool overlaps_solid(const pf::Aabb& box, const pf::TileCollisionMap& map) {
    const int left = static_cast<int>(std::floor(box.left() / pf::TileCollisionMap::tile_size));
    const int right = static_cast<int>(std::floor((box.right() - 0.001f) / pf::TileCollisionMap::tile_size));
    const int top = static_cast<int>(std::floor(box.top() / pf::TileCollisionMap::tile_size));
    const int bottom = static_cast<int>(std::floor((box.bottom() - 0.001f) / pf::TileCollisionMap::tile_size));

    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x) {
            if (map.solid_at(x, y)) {
                return true;
            }
        }
    }

    return false;
}

}

void move_player_with_collision(
    PlayerState& player,
    const pf::TileCollisionMap& map,
    float dt
) {
    player.grounded = false;

    // X axis
    player.x += player.vx * dt;

    if (overlaps_solid(player.bounds(), map)) {
        if (player.vx > 0.0f) {
            const int tile_x = static_cast<int>(std::floor((player.x + player.width) / pf::TileCollisionMap::tile_size));
            player.x = static_cast<float>(tile_x * pf::TileCollisionMap::tile_size) - player.width - 0.001f;
        } else if (player.vx < 0.0f) {
            const int tile_x = static_cast<int>(std::floor(player.x / pf::TileCollisionMap::tile_size));
            player.x = static_cast<float>((tile_x + 1) * pf::TileCollisionMap::tile_size) + 0.001f;
        }

        player.vx = 0.0f;
    }

    // Y axis
    player.y += player.vy * dt;

    if (overlaps_solid(player.bounds(), map)) {
        if (player.vy > 0.0f) {
            const int tile_y = static_cast<int>(std::floor((player.y + player.height) / pf::TileCollisionMap::tile_size));
            player.y = static_cast<float>(tile_y * pf::TileCollisionMap::tile_size) - player.height - 0.001f;
            player.grounded = true;
        } else if (player.vy < 0.0f) {
            const int tile_y = static_cast<int>(std::floor(player.y / pf::TileCollisionMap::tile_size));
            player.y = static_cast<float>((tile_y + 1) * pf::TileCollisionMap::tile_size) + 0.001f;
        }

        player.vy = 0.0f;
    }
}
