#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include <vector>

namespace pixel {

// Tile 碰撞类型
enum class TileType : u8 {
    Empty = 0,
    Solid,          // 完全固体
    OneWay,         // 单向平台（只能从上方穿过）
    SlopeLeft,      // 左斜坡
    SlopeRight,     // 右斜坡
    Hazard,         // 危险区域
};

// Tile 碰撞层
class TileCollision {
public:
    TileCollision() = default;

    // 初始化
    bool init(i32 map_width, i32 map_height, i32 tile_width, i32 tile_height);

    // 设置 tile 类型
    void set_tile(i32 x, i32 y, TileType type);
    TileType get_tile(i32 x, i32 y) const;

    // 从关卡数据加载
    void load_from_array(std::span<const TileType> tiles, i32 width, i32 height);

    // 碰撞检测：检查 AABB 是否与任何 solid tile 碰撞
    bool check_collision(const AABB& aabb) const;

    // 碰撞检测：返回所有碰撞的 tile
    std::vector<Vec2> get_colliding_tiles(const AABB& aabb) const;

    // 射线检测
    bool raycast(const Vec2& start, const Vec2& direction, f32 max_distance,
                 Vec2& hit_point, Vec2& hit_normal) const;

    // 获取 tile 的世界坐标 AABB
    AABB get_tile_bounds(i32 x, i32 y) const;

    // 尺寸
    i32 map_width() const { return m_map_width; }
    i32 map_height() const { return m_map_height; }
    i32 tile_width() const { return m_tile_width; }
    i32 tile_height() const { return m_tile_height; }

private:
    // 世界坐标转 tile 坐标
    void world_to_tile(const Vec2& world, i32& tile_x, i32& tile_y) const;

    i32 m_map_width = 0;
    i32 m_map_height = 0;
    i32 m_tile_width = 16;
    i32 m_tile_height = 16;
    std::vector<TileType> m_tiles;
};

} // namespace pixel
