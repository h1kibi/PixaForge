#include "player_physics.h"

#include <algorithm>
#include <cmath>

float approach(float current, float target, float max_delta) {
    if (current < target) {
        current += max_delta;
        if (current > target) {
            current = target;
        }
    } else if (current > target) {
        current -= max_delta;
        if (current < target) {
            current = target;
        }
    }

    return current;
}

namespace {

bool overlaps_solid(const pf::Aabb& box, const pf::TileCollisionMap& map) {
    const int ts = map.tile_size();
    const int left = static_cast<int>(std::floor(box.left() / ts));
    const int right = static_cast<int>(std::floor((box.right() - 0.001f) / ts));
    const int top = static_cast<int>(std::floor(box.top() / ts));
    const int bottom = static_cast<int>(std::floor((box.bottom() - 0.001f) / ts));

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
    const int ts = map.tile_size();

    player.was_grounded = player.grounded;
    player.grounded = false;

    // X axis
    player.x += player.vx * dt;

    if (overlaps_solid(player.bounds(), map)) {
        if (player.vx > 0.0f) {
            const int tile_x = static_cast<int>(std::floor((player.x + player.width) / ts));
            player.x = static_cast<float>(tile_x * ts) - player.width - 0.001f;
        } else if (player.vx < 0.0f) {
            const int tile_x = static_cast<int>(std::floor(player.x / ts));
            player.x = static_cast<float>((tile_x + 1) * ts) + 0.001f;
        }

        player.vx = 0.0f;
    }

    // Y axis
    player.y += player.vy * dt;

    if (overlaps_solid(player.bounds(), map)) {
        if (player.vy > 0.0f) {
            const int tile_y = static_cast<int>(std::floor((player.y + player.height) / ts));
            player.y = static_cast<float>(tile_y * ts) - player.height - 0.001f;
            player.grounded = true;
        } else if (player.vy < 0.0f) {
            const int tile_y = static_cast<int>(std::floor(player.y / ts));
            player.y = static_cast<float>((tile_y + 1) * ts) + 0.001f;
        }

        player.vy = 0.0f;
    }

    // Landing detection
    player.just_landed = !player.was_grounded && player.grounded;

    if (player.just_landed) {
        player.jump_cut = false;
    }
}
