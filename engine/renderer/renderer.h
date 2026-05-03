#pragma once

#include "renderer/color.h"
#include "renderer/texture.h"

namespace pf {

struct Rect {
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;
};

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual bool initialize(void* native_window, int virtual_width, int virtual_height) = 0;
    virtual void shutdown() = 0;

    virtual void begin_frame(Color clear_color) = 0;
    virtual void draw_texture(TextureHandle texture, const Rect& src, const Rect& dst) = 0;
    virtual void end_frame() = 0;

    virtual TextureHandle create_debug_texture_16x16() = 0;
};

}
