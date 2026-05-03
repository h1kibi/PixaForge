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

    pf::Aabb bounds() const {
        return pf::Aabb {
            x,
            y,
            width,
            height
        };
    }
};
