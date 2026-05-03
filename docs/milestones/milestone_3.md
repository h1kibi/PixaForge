# Milestone 3: Platformer Feel

## Goals

- Add gravity
- Add jump input
- Add player velocity
- Add AABB collision
- Add hardcoded tile collision grid
- Resolve movement on X and Y axes separately
- Add grounded detection
- Add coyote time
- Add jump buffer

## Non-goals

- LDtk loading
- Slopes
- One-way platforms
- Animation
- Enemy AI
- Full ECS
- Box2D integration

## Parameters

- move_speed: 85 px/s
- jump_speed: 245 px/s
- gravity: 780 px/s²
- max_fall_speed: 360 px/s
- coyote_time: 0.10 s
- jump_buffer_time: 0.12 s
- collider: 12×16
- sprite: 16×16

## Checklist

- [ ] Gravity applied each frame
- [ ] Space/W/Up jumps
- [ ] A/D moves horizontally
- [ ] Player lands on platforms
- [ ] Player stops at walls
- [ ] Coyote time works
- [ ] Jump buffer works
- [ ] Pixel-perfect rendering maintained
