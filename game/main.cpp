#include <SDL3/SDL.h>

#include <cstdio>

#include "core/version.h"
#include "renderer/backends/sdl_renderer_backend.h"

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
    std::printf("Entering main loop...\n");

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                running = false;
            }
        }

        renderer.begin_frame(pf::Color{ 18, 18, 24, 255 });

        renderer.draw_texture(
            player_texture,
            pf::Rect{ 0.0f, 0.0f, 16.0f, 16.0f },
            pf::Rect{ 152.0f, 82.0f, 16.0f, 16.0f }
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
