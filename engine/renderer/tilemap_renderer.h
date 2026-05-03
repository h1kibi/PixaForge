#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include <vector>

namespace pixel {

// Tilemap 渲染器 - 处理大地图的分块渲染
class TilemapRenderer {
public:
    TilemapRenderer() = default;

    // 初始化
    bool init(i32 map_width, i32 map_height,
              i32 tile_width, i32 tile_height);

    // 设置 tile 数据
    void set_tile(i32 x, i32 y, i32 tile_id);
    i32 get_tile(i32 x, i32 y) const;

    // 加载整个 tilemap
    void load_from_array(std::span<const i32> tiles, i32 width, i32 height);

    // 渲染（只渲染摄像机可见的 chunk）
    void render(Renderer& renderer, TextureHandle tileset, const Camera& camera);

    // 尺寸
    i32 map_width() const { return m_map_width; }
    i32 map_height() const { return m_map_height; }
    i32 tile_width() const { return m_tile_width; }
    i32 tile_height() const { return m_tile_height; }

private:
    i32 m_map_width = 0;
    i32 m_map_height = 0;
    i32 m_tile_width = 0;
    i32 m_tile_height = 0;
    std::vector<i32> m_tiles;

    // Chunk 大小（以 tile 为单位）
    static constexpr i32 CHUNK_SIZE = 16;
};

} // namespace pixel
