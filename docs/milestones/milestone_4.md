# Milestone 4: LDtk Level Import

## Goals

- Load a simple single-file LDtk project
- Parse one level
- Parse an IntGrid collision layer
- Parse a PlayerSpawn entity
- Replace the hardcoded collision map
- Spawn the player from LDtk data

## Non-goals

- Tileset rendering
- External level files
- Multi-level transitions
- Auto layers
- Enemy spawning
- Trigger volumes
- Custom editor

## LDtk Setup

- Single file .ldtk (no external levels)
- Tile size: 16
- Level size: 320 x 180 or 320 x 192
- Layer "Collision": IntGrid (0=empty, 1=solid)
- Entity "PlayerSpawn": 16x16

## Checklist

- [ ] vcpkg adds nlohmann-json
- [ ] Read .ldtk file
- [ ] Parse first level dimensions
- [ ] Parse Collision IntGrid
- [ ] Parse PlayerSpawn entity
- [ ] TileCollisionMap becomes dynamic size
- [ ] Collision from LDtk, not hardcoded
- [ ] Player spawn from LDtk
- [ ] Collision tiles still drawn as rects
- [ ] Movement, jump, double jump all work
