#include <SDL3/SDL.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "core/version.h"
#include "input/input.h"
#include "input/sdl_input.h"
#include "renderer/backends/sdl_renderer_backend.h"

struct PlayerState {
    float x = 152.0f;
    float y = 82.0f;
    float speed = 80.0f;
};

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
    std::printf("Milestone 2: Input and movement.\n");
    std::printf("Entering main loop...\n");

    constexpr float fixed_dt = 1.0f / 60.0f;

    float accumulator = 0.0f;
    std::uint64_t previous_ticks = SDL_GetTicks();

    pf::Input input;
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
            player.x += move_x * player.speed * fixed_dt;

            accumulator -= fixed_dt;
        }

        const float render_x = std::round(player.x);
        const float render_y = std::round(player.y);

        renderer.begin_frame(pf::Color{18, 18, 24, 255});

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
