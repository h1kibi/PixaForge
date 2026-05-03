#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "../world/entity.h"
#include "aabb.h"
#include "tile_collision.h"
#include <vector>

namespace pixel {

// 碰撞世界 - 管理所有碰撞体
class CollisionWorld {
public:
    CollisionWorld() = default;

    // 初始化 tile 碰撞
    void init_tilemap(i32 map_width, i32 map_height,
                      i32 tile_width, i32 tile_height);

    // 设置 tile
    void set_tile(i32 x, i32 y, TileType type);

    // 移动实体并处理碰撞
    // 返回修正后的位置
    Vec2 move_entity(Entity entity, const AABB& bounds,
                     const Vec2& velocity, f32 dt,
                     CollisionMask mask = CollisionMask::All);

    // 检测实体与 tile 的碰撞
    bool check_tile_collision(const AABB& bounds) const;

    // 获取实体下方的地面高度
    f32 get_ground_height(const AABB& bounds) const;

    // 射线检测
    bool raycast(const Vec2& start, const Vec2& direction,
                 f32 max_distance, RaycastHit& result,
                 CollisionMask mask = CollisionMask::All) const;

    // 获取 tile 碰撞层
    TileCollision& tile_collision() { return m_tile_collision; }
    const TileCollision& tile_collision() const { return m_tile_collision; }

private:
    // 分离轴解析
    Vec2 resolve_x(const AABB& bounds, const Vec2& velocity, f32 dt);
    Vec2 resolve_y(const AABB& bounds, const Vec2& velocity, f32 dt);

    TileCollision m_tile_collision;
};

} // namespace pixel
