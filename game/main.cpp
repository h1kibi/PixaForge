#include <SDL3/SDL.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "core/version.h"
#include "collision/tile_collision.h"
#include "input/input.h"
#include "input/sdl_input.h"
#include "level/ldtk_loader.h"
#include "level/level_data.h"
#include "renderer/backends/sdl_renderer_backend.h"
#include "platformer_tuning.h"
#include "player_state.h"
#include "player_physics.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    std::printf("%s v0.1.0\n", pf::engine_name());
    std::printf("Initializing SDL3...\n");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "PixaForge",
        1280,
        720,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    pf::SdlRendererBackend renderer;

    if (!renderer.initialize(window, 320, 180)) {
        std::printf("Renderer initialization failed.\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    pf::TextureHandle player_texture = renderer.create_debug_texture_16x16();

    // Load LDtk level
    pf::LevelData level;
    pf::LdtkLoader loader;

    if (!loader.load_project("assets_raw/levels/test_platformer.ldtk", level)) {
        std::printf("Failed to load level.\n");
        renderer.shutdown();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    pf::TileCollisionMap collision_map;
    collision_map.load_from_level_collision(level.collision);

    std::printf("Window and renderer created successfully.\n");
    std::printf("Milestone 4: LDtk level import.\n");
    std::printf("Entering main loop...\n");

    constexpr float fixed_dt = 1.0f / 60.0f;

    PlatformerTuning tuning;

    float accumulator = 0.0f;
    std::uint64_t previous_ticks = SDL_GetTicks();

    pf::Input input;
    PlayerState player;

    // Set spawn from LDtk
    if (level.has_player_spawn) {
        player.x = level.player_spawn.x;
        player.y = level.player_spawn.y;
    }

    bool running = true;

    while (running) {
        std::uint64_t current_ticks = SDL_GetTicks();
        float frame_time = static_cast<float>(current_ticks - previous_ticks) / 1000.0f;
        previous_ticks = current_ticks;

        if (frame_time > 0.25f) {
            frame_time = 0.25f;
        }

        accumulator += frame_time;

        input.begin_frame();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            pf::handle_sdl_input_event(input, event);
        }

        if (input.pressed(pf::Action::Quit)) {
            running = false;
        }

        while (accumulator >= fixed_dt) {
            // Track grounded state
            player.was_grounded = player.grounded;

            // Horizontal movement
            const float move_x = input.axis_move_x();
            const float target_vx = move_x * tuning.max_run_speed;

            const bool has_input = move_x != 0.0f;
            const bool turning =
                has_input &&
                player.vx != 0.0f &&
                ((move_x > 0.0f && player.vx < 0.0f) ||
                 (move_x < 0.0f && player.vx > 0.0f));

            float accel = 0.0f;

            if (player.grounded) {
                if (!has_input) {
                    accel = tuning.ground_decel;
                } else if (turning) {
                    accel = tuning.ground_turn_accel;
                } else {
                    accel = tuning.ground_accel;
                }
            } else {
                if (!has_input) {
                    accel = tuning.air_decel;
                } else if (turning) {
                    accel = tuning.air_turn_accel;
                } else {
                    accel = tuning.air_accel;
                }
            }

            player.vx = approach(
                player.vx,
                target_vx,
                accel * fixed_dt
            );

            // Jump buffer
            if (input.consume_pressed(pf::Action::Jump)) {
                player.jump_buffer_timer = tuning.jump_buffer_time;
            } else {
                player.jump_buffer_timer -= fixed_dt;
                if (player.jump_buffer_timer < 0.0f) {
                    player.jump_buffer_timer = 0.0f;
                }
            }

            // Coyote time
            if (player.grounded) {
                player.coyote_timer = tuning.coyote_time;
            } else {
                player.coyote_timer -= fixed_dt;
                if (player.coyote_timer < 0.0f) {
                    player.coyote_timer = 0.0f;
                }
            }

            // Determine if we can jump
            const bool can_ground_jump =
                player.grounded ||
                player.coyote_timer > 0.0f;

            const bool can_air_jump =
                !can_ground_jump &&
                player.jumps_used < tuning.max_jumps;

            // Execute jump
            if (player.jump_buffer_timer > 0.0f && (can_ground_jump || can_air_jump)) {
                if (can_ground_jump) {
                    player.vy = -tuning.jump_speed;
                    player.jumps_used = 1;
                } else {
                    player.vy = -tuning.double_jump_speed;
                    player.jumps_used += 1;
                }

                player.grounded = false;
                player.coyote_timer = 0.0f;
                player.jump_buffer_timer = 0.0f;
                player.jump_cut = false;
            }

            // Variable jump height
            if (input.consume_released(pf::Action::Jump) && player.vy < 0.0f) {
                player.jump_cut = true;
            }

            // Gravity
            float gravity = tuning.gravity_down;

            if (player.vy < 0.0f) {
                gravity = player.jump_cut
                    ? tuning.gravity_jump_cut
                    : tuning.gravity_up;
            }

            player.vy += gravity * fixed_dt;

            if (player.vy > tuning.max_fall_speed) {
                player.vy = tuning.max_fall_speed;
            }

            // Collision
            move_player_with_collision(player, collision_map, fixed_dt);

            // Landing detection and reset
            player.just_landed = !player.was_grounded && player.grounded;

            if (player.grounded) {
                player.jumps_used = 0;
            }

            if (player.just_landed) {
                player.jump_cut = false;
            }

            accumulator -= fixed_dt;
        }

        // Render
        const float render_x = std::round(player.x - 2.0f);
        const float render_y = std::round(player.y);

        renderer.begin_frame(pf::Color{18, 18, 24, 255});

        // Draw collision tiles
        for (int y = 0; y < collision_map.height(); ++y) {
            for (int x = 0; x < collision_map.width(); ++x) {
                if (!collision_map.solid_at(x, y)) {
                    continue;
                }

                renderer.draw_rect(
                    pf::Rect {
                        static_cast<float>(x * collision_map.tile_size()),
                        static_cast<float>(y * collision_map.tile_size()),
                        static_cast<float>(collision_map.tile_size()),
                        static_cast<float>(collision_map.tile_size())
                    },
                    pf::Color { 48, 54, 72, 255 }
                );
            }
        }

        // Draw player
        renderer.draw_texture(
            player_texture,
            pf::Rect{0.0f, 0.0f, 16.0f, 16.0f},
            pf::Rect{render_x, render_y, 16.0f, 16.0f}
        );

        renderer.end_frame();
    }

    std::printf("Shutting down...\n");

    renderer.shutdown();

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::printf("PixaForge shutdown.\n");
    return 0;
}
