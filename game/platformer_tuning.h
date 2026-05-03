#pragma once

struct PlatformerTuning {
    float max_run_speed = 105.0f;

    float ground_accel = 1400.0f;
    float ground_decel = 1800.0f;
    float air_accel = 850.0f;
    float air_decel = 650.0f;

    float jump_speed = 275.0f;

    float gravity_up = 850.0f;
    float gravity_down = 1250.0f;
    float gravity_jump_cut = 1800.0f;

    float max_fall_speed = 420.0f;

    float coyote_time = 0.10f;
    float jump_buffer_time = 0.12f;
};
