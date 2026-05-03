#include <SDL3/SDL.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "core/version.h"
#include "collision/tile_collision.h"
#include "input/input.h"
#include "input/sdl_input.h"
#include "renderer/backends/sdl_renderer_backend.h"
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

    std::printf("Window and renderer created successfully.\n");
    std::printf("Milestone 3: Platformer feel.\n");
    std::printf("Entering main loop...\n");

    constexpr float fixed_dt = 1.0f / 60.0f;
    constexpr float coyote_time = 0.10f;
    constexpr float jump_buffer_time = 0.12f;

    float accumulator = 0.0f;
    std::uint64_t previous_ticks = SDL_GetTicks();

    pf::Input input;
    pf::TileCollisionMap collision_map;
    PlayerState player;
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
        }

        pf::update_input_from_sdl_keyboard(input);

        if (input.pressed(pf::Action::Quit)) {
            running = false;
        }

        while (accumulator >= fixed_dt) {
            const float move_x = input.axis_move_x();

            player.vx = move_x * player.move_speed;

            // Jump buffer
            if (input.pressed(pf::Action::Jump)) {
                player.jump_buffer_timer = jump_buffer_time;
            } else {
                player.jump_buffer_timer -= fixed_dt;
                if (player.jump_buffer_timer < 0.0f) {
                    player.jump_buffer_timer = 0.0f;
                }
            }

            // Coyote time
            if (player.grounded) {
                player.coyote_timer = coyote_time;
            } else {
                player.coyote_timer -= fixed_dt;
                if (player.coyote_timer < 0.0f) {
                    player.coyote_timer = 0.0f;
                }
            }

            // Jump execution
            const bool can_jump = player.grounded || player.coyote_timer > 0.0f;

            if (player.jump_buffer_timer > 0.0f && can_jump) {
                player.vy = -player.jump_speed;
                player.grounded = false;
                player.coyote_timer = 0.0f;
                player.jump_buffer_timer = 0.0f;
            }

            // Gravity
            player.vy += player.gravity * fixed_dt;

            if (player.vy > player.max_fall_speed) {
                player.vy = player.max_fall_speed;
            }

            // Collision
            move_player_with_collision(player, collision_map, fixed_dt);

            accumulator -= fixed_dt;
        }

        // Render
        const float render_x = std::round(player.x - 2.0f);
        const float render_y = std::round(player.y);

        renderer.begin_frame(pf::Color{18, 18, 24, 255});

        // Draw collision tiles
        for (int y = 0; y < pf::TileCollisionMap::height; ++y) {
            for (int x = 0; x < pf::TileCollisionMap::width; ++x) {
                if (!collision_map.solid_at(x, y)) {
                    continue;
                }

                renderer.draw_rect(
                    pf::Rect {
                        static_cast<float>(x * pf::TileCollisionMap::tile_size),
                        static_cast<float>(y * pf::TileCollisionMap::tile_size),
                        static_cast<float>(pf::TileCollisionMap::tile_size),
                        static_cast<float>(pf::TileCollisionMap::tile_size)
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
