# Milestone 0: Window and Main Loop

## Goals

- Configure CMake successfully
- Build the engine static library
- Build the game executable
- Open an SDL3 window
- Process quit events
- Shutdown cleanly

## Non-goals

- Rendering sprites
- Input mapping
- Audio
- ImGui
- ECS
- Collision
- LDtk

## Checklist

- [x] CMake project structure
- [x] vcpkg manifest with SDL3
- [x] PixaForge static library compiles
- [x] Game executable links against PixaForge and SDL3
- [x] SDL_Init with VIDEO, GAMEPAD, AUDIO
- [x] SDL_CreateWindow 1280x720 resizable
- [x] SDL_PollEvent loop
- [x] SDL_EVENT_QUIT handling
- [x] SDL_DestroyWindow and SDL_Quit on exit

## Build Instructions

```bash
# Clone repository
git clone https://github.com/h1kibi/PixaForge.git
cd PixaForge

# Install dependencies (requires vcpkg)
vcpkg install sdl3

# Build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
cmake --build .

# Run
./bin/game
```

## Expected Output

```
PixaForge v0.1.0
Initializing SDL3...
Window created successfully.
Entering main loop...
Shutting down...
PixaForge shutdown.
```
