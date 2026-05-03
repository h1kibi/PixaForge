# Milestone 3.5: Platformer Feel Tuning

## Goals

- Tune movement and jump feel before LDtk integration
- Add acceleration and deceleration
- Add separate ground and air control
- Add variable jump height
- Add stronger fall gravity
- Centralize platformer tuning values
- Keep coyote time and jump buffer working

## Non-goals

- LDtk loading
- Animation
- Camera follow
- Enemy AI
- One-way platforms
- Slopes
- ImGui tuning UI

## Parameters (Snappy Profile)

- max_run_speed: 110 px/s
- ground_accel: 1600 px/s²
- ground_decel: 2000 px/s²
- air_accel: 900 px/s²
- air_decel: 650 px/s²
- jump_speed: 280 px/s
- gravity_up: 875 px/s²
- gravity_down: 1300 px/s²
- gravity_jump_cut: 2000 px/s²
- max_fall_speed: 440 px/s

## Checklist

- [ ] Short hop by tapping jump
- [ ] Full jump by holding jump
- [ ] Faster fall than rise
- [ ] Ground acceleration/deceleration
- [ ] Air control weaker than ground
- [ ] Quick ground turnaround
- [ ] Landing state detection
