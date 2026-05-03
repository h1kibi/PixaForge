# Milestone 5: Playable Demo Level

## Goals

- Build a 3-5 minute playable pixel platformer level
- Use LDtk as the level source
- Add checkpoints, hazards, goal
- Add at least one dynamic threat (patrol enemy)
- Show level state in window title
- Player can complete the level

## Non-goals

- Main menu
- Save system
- Audio system
- Animation system
- Tileset rendering
- Multi-level progression
- Lua scripting
- Box2D physics
- Particles
- Camera follow
- Full UI

## Level Structure

- Area 1: Basic movement and jumping
- Area 2: Double jump introduction
- Area 3: Hazards + Checkpoint
- Area 4: Patrol enemy
- Area 5: Goal

## Checklist

- [ ] GameState struct extracted
- [ ] load_level_runtime() function
- [ ] Window title shows state
- [ ] Enemy patrol entity parsed from LDtk
- [ ] Patrol enemy runtime (moves, kills player)
- [ ] Demo level built in LDtk
- [ ] Level complete state
- [ ] R key reloads level
