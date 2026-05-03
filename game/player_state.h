#pragma once

#include "collision/aabb.h"

struct PlayerState {
    float x = 152.0f;
    float y = 120.0f;

    float vx = 0.0f;
    float vy = 0.0f;

    float width = 12.0f;
    float height = 16.0f;

    float move_speed = 85.0f;
    float jump_speed = 245.0f;
    float gravity = 780.0f;
    float max_fall_speed = 360.0f;

    bool grounded = false;

    float coyote_timer = 0.0f;
    float jump_buffer_timer = 0.0f;

    pf::Aabb bounds() const {
        return pf::Aabb {
            x,
            y,
            width,
            height
        };
    }
};
