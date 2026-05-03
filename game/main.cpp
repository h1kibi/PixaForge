#include <SDL3/SDL.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "core/version.h"
#include "collision/tile_collision.h"
#include "input/input.h"
#include "input/sdl_input.h"
#include "renderer/backends/sdl_renderer_backend.h"
#include "platformer_tuning.h"
#include "player_state.h"
#include "player_physics.h"
#include "game_state.h"

namespace {

bool overlaps_rect(const pf::Aabb& box, const pf::LevelRect& rect) {
    return box.left() < rect.x + rect.w &&
           box.right() > rect.x &&
           box.top() < rect.y + rect.h &&
           box.bottom() > rect.y;
}

bool overlaps_aabb(const pf::Aabb& a, const pf::Aabb& b) {
    return a.left() < b.right() &&
           a.right() > b.left() &&
           a.top() < b.bottom() &&
           a.bottom() > b.top();
}

void update_window_title(SDL_Window* window, const GameState& state, int checkpoint) {
    if (state.level_complete) {
        SDL_SetWindowTitle(window, "PixaForge - Level Complete!");
    } else if (checkpoint >= 0) {
        char title[64];
        std::snprintf(title, sizeof(title), "PixaForge - Checkpoint %d", checkpoint + 1);
        SDL_SetWindowTitle(window, title);
    } else {
        SDL_SetWindowTitle(window, "PixaForge - Playing");
    }
}

}

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

    // Load level
    GameState state;
    const std::string level_path = "assets_raw/levels/test_platformer.ldtk";

    if (!load_level_runtime(level_path, state)) {
        renderer.shutdown();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::printf("Milestone 5: Playable demo.\n");
    std::printf("Controls: A/D/Arrows=Move, Space/W/Up=Jump, R=Reload, ESC=Quit\n");
    std::printf("Entering main loop...\n");

    constexpr float fixed_dt = 1.0f / 60.0f;
    PlatformerTuning tuning;

    float accumulator = 0.0f;
    std::uint64_t previous_ticks = SDL_GetTicks();

    pf::Input input;
    bool running = true;

    update_window_title(window, state, state.checkpoint_index);

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

        // Reload level
        if (input.consume_pressed(pf::Action::Reload)) {
            std::printf("Reloading level...\n");
            load_level_runtime(level_path, state);
            update_window_title(window, state, state.checkpoint_index);
        }

        while (accumulator >= fixed_dt) {
            if (state.level_complete) {
                accumulator -= fixed_dt;
                continue;
            }

            PlayerState& player = state.player;

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
            move_player_with_collision(player, state.collision_map, fixed_dt);

            // Landing detection and reset
            player.just_landed = !player.was_grounded && player.grounded;

            if (player.grounded) {
                player.jumps_used = 0;
            }

            if (player.just_landed) {
                player.jump_cut = false;
            }

            // Update enemies
            for (auto& enemy : state.enemies) {
                enemy.x += enemy.vx * fixed_dt;

                if (enemy.x > enemy.start_x + enemy.patrol_distance) {
                    enemy.x = enemy.start_x + enemy.patrol_distance;
                    enemy.vx = -enemy.vx;
                } else if (enemy.x < enemy.start_x) {
                    enemy.x = enemy.start_x;
                    enemy.vx = -enemy.vx;
                }
            }

            // Checkpoint activation
            for (size_t i = 0; i < state.level.checkpoints.size(); ++i) {
                const auto& cp = state.level.checkpoints[i];
                const pf::Aabb cp_bounds = {cp.x, cp.y, 16.0f, 16.0f};

                if (overlaps_aabb(player.bounds(), cp_bounds)) {
                    if (state.checkpoint_index != static_cast<int>(i)) {
                        state.checkpoint_index = static_cast<int>(i);
                        state.spawn_x = cp.x;
                        state.spawn_y = cp.y;
                        update_window_title(window, state, state.checkpoint_index);
                        std::printf("Checkpoint %d activated!\n", state.checkpoint_index + 1);
                    }
                }
            }

            // Hazard collision
            bool hit_hazard = false;
            for (const auto& hazard : state.level.hazards) {
                if (overlaps_rect(player.bounds(), hazard.bounds)) {
                    hit_hazard = true;
                    break;
                }
            }

            // Enemy collision
            if (!hit_hazard) {
                for (const auto& enemy : state.enemies) {
                    if (overlaps_aabb(player.bounds(), enemy.bounds())) {
                        hit_hazard = true;
                        break;
                    }
                }
            }

            if (hit_hazard) {
                reset_player_to_spawn(state);
                std::printf("Hit hazard! Respawned.\n");
            }

            // Goal collision
            for (const auto& goal : state.level.goals) {
                if (overlaps_rect(player.bounds(), goal.bounds)) {
                    state.level_complete = true;
                    state.mode = GameMode::LevelComplete;
                    update_window_title(window, state, state.checkpoint_index);
                    std::printf("Level complete!\n");
                    break;
                }
            }

            accumulator -= fixed_dt;
        }

        // Render
        const PlayerState& player = state.player;
        const float render_x = std::round(player.x - 2.0f);
        const float render_y = std::round(player.y);

        renderer.begin_frame(pf::Color{18, 18, 24, 255});

        // Draw collision tiles
        for (int y = 0; y < state.collision_map.height(); ++y) {
            for (int x = 0; x < state.collision_map.width(); ++x) {
                if (!state.collision_map.solid_at(x, y)) {
                    continue;
                }

                renderer.draw_rect(
                    pf::Rect {
                        static_cast<float>(x * state.collision_map.tile_size()),
                        static_cast<float>(y * state.collision_map.tile_size()),
                        static_cast<float>(state.collision_map.tile_size()),
                        static_cast<float>(state.collision_map.tile_size())
                    },
                    pf::Color { 48, 54, 72, 255 }
                );
            }
        }

        // Draw checkpoints
        for (const auto& cp : state.level.checkpoints) {
            renderer.draw_rect(
                pf::Rect{cp.x, cp.y, 16.0f, 16.0f},
                pf::Color{0, 200, 100, 255}
            );
        }

        // Draw hazards
        for (const auto& hazard : state.level.hazards) {
            renderer.draw_rect(
                pf::Rect{hazard.bounds.x, hazard.bounds.y, hazard.bounds.w, hazard.bounds.h},
                pf::Color{200, 50, 50, 255}
            );
        }

        // Draw goals
        for (const auto& goal : state.level.goals) {
            renderer.draw_rect(
                pf::Rect{goal.bounds.x, goal.bounds.y, goal.bounds.w, goal.bounds.h},
                pf::Color{255, 215, 0, 255}
            );
        }

        // Draw enemies
        for (const auto& enemy : state.enemies) {
            renderer.draw_rect(
                pf::Rect{enemy.x, enemy.y, enemy.width, enemy.height},
                pf::Color{200, 100, 255, 255}
            );
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
