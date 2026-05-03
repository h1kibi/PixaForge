#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "../renderer/renderer.h"

namespace pixel {

// 碰撞调试绘制
class CollisionDebugDraw {
public:
    CollisionDebugDraw() = default;

    // 设置是否显示
    void set_visible(bool visible) { m_visible = visible; }
    bool is_visible() const { return m_visible; }

    // 绘制碰撞层
    void draw_tilemap(Renderer& renderer, const class TileCollision& tile_collision,
                      const Camera& camera);

    // 绘制 AABB
    void draw_aabb(Renderer& renderer, const AABB& aabb,
                   const Color& color = Color::green());

    // 绘制所有实体的碰撞体
    void draw_world(Renderer& renderer, const class World& world);

private:
    bool m_visible = false;
};

} // namespace pixel
