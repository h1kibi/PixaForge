#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include <vector>

namespace pixel {

// Tilemap - 管理 tile 数据和渲染
class Tilemap {
public:
    Tilemap() = default;

    // 初始化
    bool init(i32 width, i32 height, i32 tile_width, i32 tile_height);

    // 设置/获取 tile
    void set_tile(i32 x, i32 y, i32 tile_id);
    i32 get_tile(i32 x, i32 y) const;

    // 从数组加载
    void load_from_array(std::span<const i32> data, i32 width, i32 height);

    // 清空
    void clear();

    // 尺寸
    i32 width() const { return m_width; }
    i32 height() const { return m_height; }
    i32 tile_width() const { return m_tile_width; }
    i32 tile_height() const { return m_tile_height; }

    // 世界尺寸（像素）
    i32 world_width() const { return m_width * m_tile_width; }
    i32 world_height() const { return m_height * m_tile_height; }

    // 获取 tile 数据
    const std::vector<i32>& data() const { return m_tiles; }

    // 世界坐标转 tile 坐标
    void world_to_tile(const Vec2& world, i32& tile_x, i32& tile_y) const {
        tile_x = static_cast<i32>(world.x / m_tile_width);
        tile_y = static_cast<i32>(world.y / m_tile_height);
    }

    // tile 坐标转世界坐标
    Vec2 tile_to_world(i32 tile_x, i32 tile_y) const {
        return Vec2{
            static_cast<f32>(tile_x * m_tile_width),
            static_cast<f32>(tile_y * m_tile_height)
        };
    }

private:
    i32 m_width = 0;
    i32 m_height = 0;
    i32 m_tile_width = 16;
    i32 m_tile_height = 16;
    std::vector<i32> m_tiles;
};

} // namespace pixel
