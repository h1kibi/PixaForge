#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "renderer/renderer.h"

namespace pf {

class SdlRendererBackend final : public Renderer {
public:
    bool initialize(void* native_window, int virtual_width, int virtual_height) override;
    void shutdown() override;

    void begin_frame(Color clear_color) override;
    void draw_texture(TextureHandle texture, const Rect& src, const Rect& dst) override;
    void draw_rect(const Rect& rect, Color color) override;
    void end_frame() override;

    TextureHandle create_debug_texture_16x16() override;

private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    SDL_Texture* virtual_canvas_ = nullptr;

    int virtual_width_ = 320;
    int virtual_height_ = 180;

    std::vector<SDL_Texture*> textures_;

    SDL_Texture* get_texture(TextureHandle handle);
    SDL_FRect calculate_integer_scaled_viewport() const;
};

}
