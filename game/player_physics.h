#pragma once

#include "collision/tile_collision.h"
#include "platformer_tuning.h"
#include "player_state.h"

void move_player_with_collision(
    PlayerState& player,
    const pf::TileCollisionMap& map,
    float dt
);

float approach(float current, float target, float max_delta);
