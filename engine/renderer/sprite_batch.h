#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "../renderer/texture.h"
#include "../renderer/renderer.h"
#include <vector>

namespace pixel {

// Sprite Batch - 用于高效批量绘制精灵
class SpriteBatch {
public:
    SpriteBatch() = default;

    void begin();
    void end();

    // 添加精灵到批次
    void draw(TextureHandle texture,
              const Rect& source,
              const Rect& dest,
              const Color& color = Color::white(),
              f32 rotation = 0.0f,
              bool flip_x = false,
              bool flip_y = false);

    // 清空批次
    void clear();

    // 提交到渲染器
    void submit(Renderer& renderer);

    // 统计
    i32 sprite_count() const { return static_cast<i32>(m_cmds.size()); }

private:
    std::vector<SpriteDrawCmd> m_cmds;
    bool m_active = false;
};

// Tilemap Batch - 用于高效绘制 tilemap
class TilemapBatch {
public:
    TilemapBatch() = default;

    // 设置 tileset 纹理
    void set_tileset(TextureHandle texture, i32 tile_width, i32 tile_height);

    // 添加 tile
    void add_tile(i32 tile_id, i32 grid_x, i32 grid_y);

    // 清空
    void clear();

    // 提交到渲染器（只绘制摄像机可见范围）
    void submit(Renderer& renderer, const Camera& camera);

    // 统计
    i32 tile_count() const { return m_tile_count; }

private:
    TextureHandle m_tileset = {};
    i32 m_tile_width = 0;
    i32 m_tile_height = 0;

    struct TileEntry {
        i32 tile_id;
        i32 grid_x;
        i32 grid_y;
    };
    std::vector<TileEntry> m_tiles;
    i32 m_tile_count = 0;
};

} // namespace pixel
