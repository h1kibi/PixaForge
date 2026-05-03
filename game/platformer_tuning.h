#pragma once

struct PlatformerTuning {
    float max_run_speed = 115.0f;

    float ground_accel = 4200.0f;
    float ground_turn_accel = 6200.0f;
    float ground_decel = 5200.0f;

    float air_accel = 1500.0f;
    float air_turn_accel = 2200.0f;
    float air_decel = 900.0f;

    float jump_speed = 280.0f;

    float gravity_up = 875.0f;
    float gravity_down = 1300.0f;
    float gravity_jump_cut = 2000.0f;

    float max_fall_speed = 440.0f;

    float coyote_time = 0.10f;
    float jump_buffer_time = 0.12f;
};
