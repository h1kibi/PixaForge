#pragma once

#include "collision/aabb.h"
#include "platformer_tuning.h"

struct PlayerState {
    float x = 152.0f;
    float y = 120.0f;

    float vx = 0.0f;
    float vy = 0.0f;

    float width = 12.0f;
    float height = 16.0f;

    bool grounded = false;
    bool was_grounded = false;
    bool just_landed = false;
    bool jump_cut = false;

    float coyote_timer = 0.0f;
    float jump_buffer_timer = 0.0f;

    int jumps_used = 0;

    pf::Aabb bounds() const {
        return pf::Aabb {
            x,
            y,
            width,
            height
        };
    }
};

struct EnemyState {
    float x = 0.0f;
    float y = 0.0f;
    float vx = 30.0f;
    float start_x = 0.0f;
    float patrol_distance = 48.0f;
    float width = 16.0f;
    float height = 16.0f;

    pf::Aabb bounds() const {
        return pf::Aabb {
            x,
            y,
            width,
            height
        };
    }
};
