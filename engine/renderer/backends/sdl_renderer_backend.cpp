#include "renderer/backends/sdl_renderer_backend.h"

#include <cstdio>
#include <algorithm>

namespace pf {

bool SdlRendererBackend::initialize(void* native_window, int virtual_width, int virtual_height) {
    window_ = static_cast<SDL_Window*>(native_window);
    virtual_width_ = virtual_width;
    virtual_height_ = virtual_height;

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
        std::printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderVSync(renderer_, 1);

    virtual_canvas_ = SDL_CreateTexture(
        renderer_,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        virtual_width_,
        virtual_height_
    );

    if (!virtual_canvas_) {
        std::printf("SDL_CreateTexture virtual canvas failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetTextureScaleMode(virtual_canvas_, SDL_SCALEMODE_NEAREST);

    textures_.push_back(nullptr); // handle 0 is invalid

    return true;
}

void SdlRendererBackend::shutdown() {
    for (SDL_Texture* texture : textures_) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    textures_.clear();

    if (virtual_canvas_) {
        SDL_DestroyTexture(virtual_canvas_);
        virtual_canvas_ = nullptr;
    }

    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    window_ = nullptr;
}

void SdlRendererBackend::begin_frame(Color clear_color) {
    SDL_SetRenderTarget(renderer_, virtual_canvas_);

    SDL_SetRenderDrawColor(
        renderer_,
        clear_color.r,
        clear_color.g,
        clear_color.b,
        clear_color.a
    );

    SDL_RenderClear(renderer_);
}

void SdlRendererBackend::draw_texture(TextureHandle texture, const Rect& src, const Rect& dst) {
    SDL_Texture* sdl_texture = get_texture(texture);
    if (!sdl_texture) {
        return;
    }

    SDL_FRect sdl_src {
        src.x,
        src.y,
        src.w,
        src.h
    };

    SDL_FRect sdl_dst {
        dst.x,
        dst.y,
        dst.w,
        dst.h
    };

    SDL_RenderTexture(renderer_, sdl_texture, &sdl_src, &sdl_dst);
}

void SdlRendererBackend::end_frame() {
    SDL_SetRenderTarget(renderer_, nullptr);

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    SDL_FRect viewport = calculate_integer_scaled_viewport();

    SDL_SetTextureScaleMode(virtual_canvas_, SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer_, virtual_canvas_, nullptr, &viewport);

    SDL_RenderPresent(renderer_);
}

TextureHandle SdlRendererBackend::create_debug_texture_16x16() {
    constexpr int width = 16;
    constexpr int height = 16;

    std::uint32_t pixels[width * height] = {};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const bool border = x == 0 || y == 0 || x == width - 1 || y == height - 1;
            const bool face = x >= 5 && x <= 10 && y >= 4 && y <= 11;
            const bool eye = (x == 6 || x == 9) && y == 7;

            std::uint32_t color = 0x00000000;

            if (border) {
                color = 0xFF202020;
            } else if (eye) {
                color = 0xFF000000;
            } else if (face) {
                color = 0xFFFFCC66;
            } else {
                color = 0xFF4A90E2;
            }

            pixels[y * width + x] = color;
        }
    }

    SDL_Texture* texture = SDL_CreateTexture(
        renderer_,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC,
        width,
        height
    );

    if (!texture) {
        std::printf("SDL_CreateTexture debug texture failed: %s\n", SDL_GetError());
        return {};
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(std::uint32_t));

    textures_.push_back(texture);

    return TextureHandle {
        static_cast<std::uint32_t>(textures_.size() - 1)
    };
}

SDL_Texture* SdlRendererBackend::get_texture(TextureHandle handle) {
    if (handle.id == 0 || handle.id >= textures_.size()) {
        return nullptr;
    }

    return textures_[handle.id];
}

SDL_FRect SdlRendererBackend::calculate_integer_scaled_viewport() const {
    int window_width = 0;
    int window_height = 0;
    SDL_GetWindowSize(window_, &window_width, &window_height);

    const int scale_x = window_width / virtual_width_;
    const int scale_y = window_height / virtual_height_;
    const int scale = std::max(1, std::min(scale_x, scale_y));

    const int output_width = virtual_width_ * scale;
    const int output_height = virtual_height_ * scale;

    const int offset_x = (window_width - output_width) / 2;
    const int offset_y = (window_height - output_height) / 2;

    return SDL_FRect {
        static_cast<float>(offset_x),
        static_cast<float>(offset_y),
        static_cast<float>(output_width),
        static_cast<float>(output_height)
    };
}

}
