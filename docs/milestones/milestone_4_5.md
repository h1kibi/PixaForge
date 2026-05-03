# Milestone 4.5: LDtk Level Iteration

## Goals

- Make LDtk the source of truth for test levels
- Add reload support
- Parse basic gameplay entities
- Add checkpoint, hazard, and goal entities
- Improve level loading diagnostics

## Non-goals

- Full tileset rendering
- Enemy AI
- Save system
- Menus
- Audio
- Animation

## LDtk Entities

- PlayerSpawn: px position
- Checkpoint: px position
- Hazard: px + width/height (rect)
- Goal: px + width/height (rect)

## Checklist

- [ ] R key reloads LDtk level
- [ ] Hazard resets player to spawn/checkpoint
- [ ] Checkpoint updates respawn point
- [ ] Goal triggers level complete
- [ ] Level loading logs are clear
