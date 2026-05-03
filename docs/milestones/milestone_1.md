# Milestone 1: Render a Pixel Character

## Goals

- Create an SDL_Renderer backend
- Render to a 320x180 virtual canvas
- Scale the virtual canvas to the window using integer scaling
- Draw a generated 16x16 pixel character
- Keep pixels crisp when resizing the window

## Non-goals

- PNG loading
- Sprite batching
- Tilemap rendering
- Animation
- Camera movement
- ImGui
- Asset pipeline

## Checklist

- [ ] Renderer interface (color.h, texture.h, renderer.h)
- [ ] SDL renderer backend implementation
- [ ] Virtual canvas 320x180
- [ ] Integer scaling calculation
- [ ] SDL_SCALEMODE_NEAREST for pixel crispness
- [ ] Debug 16x16 texture generation
- [ ] Draw texture at center of virtual canvas
- [ ] ESC key to quit

## Expected Result

- Dark blue background (RGB 18, 18, 24)
- 16x16 pixel character centered on screen
- Character remains crisp when resizing window
- Black borders on non-uniform aspect ratios
