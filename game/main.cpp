#include <SDL3/SDL.h>

#include <cstdio>

#include "core/version.h"

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

    std::printf("Window created successfully.\n");
    std::printf("Entering main loop...\n");

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_Delay(1);
    }

    std::printf("Shutting down...\n");

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::printf("PixaForge shutdown.\n");
    return 0;
}
