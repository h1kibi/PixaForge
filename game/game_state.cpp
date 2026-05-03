#include "game_state.h"

#include <cstdio>

#include "level/ldtk_loader.h"

bool load_level_runtime(const std::string& path, GameState& state) {
    pf::LdtkLoader loader;

    if (!loader.load_project(path, state.level)) {
        std::printf("Failed to load level: %s\n", path.c_str());
        return false;
    }

    state.collision_map.load_from_level_collision(state.level.collision);

    state.spawn_x = state.level.player_spawn.x;
    state.spawn_y = state.level.player_spawn.y;

    state.level_complete = false;
    state.mode = GameMode::Playing;
    state.checkpoint_index = -1;

    // Build enemies
    state.enemies.clear();
    for (const auto& enemy_data : state.level.enemies) {
        EnemyState enemy;
        enemy.x = enemy_data.x;
        enemy.y = enemy_data.y;
        enemy.start_x = enemy_data.x;
        enemy.vx = enemy_data.speed;
        enemy.patrol_distance = enemy_data.patrol_distance;
        enemy.width = enemy_data.width;
        enemy.height = enemy_data.height;
        state.enemies.push_back(enemy);
    }

    reset_player_to_spawn(state);

    std::printf("Level runtime loaded: %s\n", path.c_str());
    return true;
}

void reset_player_to_spawn(GameState& state) {
    state.player.x = state.spawn_x;
    state.player.y = state.spawn_y;
    state.player.vx = 0.0f;
    state.player.vy = 0.0f;
    state.player.grounded = false;
    state.player.jumps_used = 0;
}
