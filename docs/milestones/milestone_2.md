# Milestone 2: Input and Movement

## Goals

- Add an action-based input system
- Support keyboard mappings for MoveLeft, MoveRight, and Quit
- Update player movement using a fixed timestep
- Render the player at the updated position
- Keep movement frame-rate independent
- Snap rendered sprite position to integer pixels

## Non-goals

- Jumping
- Gravity
- Collision
- Tilemap
- Camera follow
- Animation
- Gamepad remapping

## Checklist

- [ ] Input class with down/pressed/released
- [ ] Action enum: MoveLeft, MoveRight, Jump, Pause, Quit
- [ ] SDL keyboard state mapping
- [ ] A/D and arrow keys move player
- [ ] ESC quits
- [ ] Fixed timestep (1/60s)
- [ ] Player position stored as float
- [ ] Render position snapped to integer pixels

## Expected Result

- Deep blue background
- 16x16 pixel character in center
- A/Left moves left, D/Right moves right
- ESC exits
- Movement speed independent of framerate
