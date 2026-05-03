#pragma once

#include <vector>

namespace pf {

struct LevelTileCollision {
    int width = 0;
    int height = 0;
    int tile_size = 16;
    std::vector<int> solid;
};

struct LevelSpawnPoint {
    float x = 0.0f;
    float y = 0.0f;
};

struct LevelData {
    int pixel_width = 0;
    int pixel_height = 0;
    LevelTileCollision collision;
    LevelSpawnPoint player_spawn;
    bool has_player_spawn = false;
};

}
