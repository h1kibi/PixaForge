#pragma once

#include <string>
#include <vector>

#include "collision/tile_collision.h"
#include "level/level_data.h"
#include "player_state.h"

enum class GameMode {
    Playing,
    LevelComplete
};

struct GameState {
    GameMode mode = GameMode::Playing;

    pf::LevelData level;
    pf::TileCollisionMap collision_map;

    PlayerState player;
    std::vector<EnemyState> enemies;

    float spawn_x = 0.0f;
    float spawn_y = 0.0f;

    bool level_complete = false;
    int checkpoint_index = -1;
};

bool load_level_runtime(const std::string& path, GameState& state);
void reset_player_to_spawn(GameState& state);
