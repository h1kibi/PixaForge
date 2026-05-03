#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "texture.h"
#include "camera.h"
#include <span>

namespace pixel {

// 渲染颜色
struct Color {
    u8 r = 255, g = 255, b = 255, a = 255;

    Color() = default;
    constexpr Color(u8 r, u8 g, u8 b, u8 a = 255) : r(r), g(g), b(b), a(a) {}

    static constexpr Color white() { return {255, 255, 255}; }
    static constexpr Color black() { return {0, 0, 0}; }
    static constexpr Color red() { return {255, 0, 0}; }
    static constexpr Color green() { return {0, 255, 0}; }
    static constexpr Color blue() { return {0, 0, 255}; }
    static constexpr Color transparent() { return {0, 0, 0, 0}; }
};

// Sprite 绘制信息
struct SpriteDrawCmd {
    TextureHandle texture;
    Rect source;      // 纹理中的区域
    Rect dest;        // 屏幕上的位置
    Color color = Color::white();
    f32 rotation = 0.0f;
    bool flip_x = false;
    bool flip_y = false;
    i32 layer = 0;    // 绘制层，用于排序
};

// 渲染器接口
class Renderer {
public:
    virtual ~Renderer() = default;

    virtual bool init(void* window_handle, i32 width, i32 height) = 0;
    virtual void shutdown() = 0;

    // 帧操作
    virtual void begin_frame(const Color& clear_color = Color::black()) = 0;
    virtual void end_frame() = 0;

    // 虚拟分辨率
    virtual void set_virtual_resolution(i32 width, i32 height) = 0;
    virtual i32 virtual_width() const = 0;
    virtual i32 virtual_height() const = 0;

    // 纹理管理
    virtual TextureHandle load_texture(std::string_view path) = 0;
    virtual void unload_texture(TextureHandle handle) = 0;
    virtual i32 texture_width(TextureHandle handle) const = 0;
    virtual i32 texture_height(TextureHandle handle) const = 0;

    // 绘制调用
    virtual void draw_sprite(const SpriteDrawCmd& cmd) = 0;
    virtual void draw_sprites(std::span<const SpriteDrawCmd> cmds) = 0;

    // 绘制矩形（调试用）
    virtual void draw_rect(const Rect& rect, const Color& color, bool filled = true) = 0;
    virtual void draw_line(const Vec2& a, const Vec2& b, const Color& color) = 0;

    // 状态
    virtual void set_camera(const Camera& camera) = 0;
    virtual i32 draw_calls() const = 0;
    virtual i32 sprites_drawn() const = 0;
};

} // namespace pixel
