#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "../world/entity.h"

namespace pixel {

// AABB 碰撞检测
namespace aabb {

// 检测两个 AABB 是否重叠
inline bool overlaps(const AABB& a, const AABB& b) {
    return a.min.x < b.max.x && a.max.x > b.min.x &&
           a.min.y < b.max.y && a.max.y > b.min.y;
}

// 计算重叠信息
inline CollisionResult check(const AABB& a, const AABB& b) {
    CollisionResult result;

    f32 overlap_x = (std::min)(a.max.x, b.max.x) - (std::max)(a.min.x, b.min.x);
    f32 overlap_y = (std::min)(a.max.y, b.max.y) - (std::max)(a.min.y, b.min.y);

    if (overlap_x <= 0.0f || overlap_y <= 0.0f) {
        return result;
    }

    result.collided = true;

    // 选择最小穿透轴
    if (overlap_x < overlap_y) {
        result.penetration = overlap_x;
        if (a.center().x < b.center().x) {
            result.normal = Vec2{-1.0f, 0.0f};
        } else {
            result.normal = Vec2{1.0f, 0.0f};
        }
    } else {
        result.penetration = overlap_y;
        if (a.center().y < b.center().y) {
            result.normal = Vec2{0.0f, -1.0f};
        } else {
            result.normal = Vec2{0.0f, 1.0f};
        }
    }

    result.contact_point = Vec2{
        (std::max)(a.min.x, b.min.x) + overlap_x * 0.5f,
        (std::max)(a.min.y, b.min.y) + overlap_y * 0.5f
    };

    return result;
}

// Swept AABB - 用于高速移动物体
inline RaycastHit sweep(const AABB& moving, const Vec2& velocity,
                        const AABB& target, f32 dt) {
    RaycastHit result;

    // 如果速度为零，直接检测重叠
    if (velocity.x == 0.0f && velocity.y == 0.0f) {
        if (overlaps(moving, target)) {
            result.hit = true;
            result.distance = 0.0f;
            result.point = moving.center();
        }
        return result;
    }

    // 计算进入和离开时间
    f32 t_enter = 0.0f;
    f32 t_exit = 1.0f;

    // X 轴
    if (velocity.x != 0.0f) {
        f32 x1 = (target.min.x - moving.max.x) / velocity.x;
        f32 x2 = (target.max.x - moving.min.x) / velocity.x;

        t_enter = (std::max)(t_enter, (std::min)(x1, x2));
        t_exit = (std::min)(t_exit, (std::max)(x1, x2));
    } else {
        if (moving.max.x <= target.min.x || moving.min.x >= target.max.x) {
            return result;
        }
    }

    // Y 轴
    if (velocity.y != 0.0f) {
        f32 y1 = (target.min.y - moving.max.y) / velocity.y;
        f32 y2 = (target.max.y - moving.min.y) / velocity.y;

        t_enter = (std::max)(t_enter, (std::min)(y1, y2));
        t_exit = (std::min)(t_exit, (std::max)(y1, y2));
    } else {
        if (moving.max.y <= target.min.y || moving.min.y >= target.max.y) {
            return result;
        }
    }

    if (t_enter > t_exit || t_enter > 1.0f || t_enter < 0.0f) {
        return result;
    }

    result.hit = true;
    result.distance = t_enter;
    result.point = moving.center() + velocity * t_enter;

    // 确定碰撞法线
    if (velocity.x != 0.0f) {
        f32 x1 = (target.min.x - moving.max.x) / velocity.x;
        if (t_enter == x1) {
            result.normal = Vec2{-1.0f, 0.0f};
        } else {
            result.normal = Vec2{1.0f, 0.0f};
        }
    } else {
        f32 y1 = (target.min.y - moving.max.y) / velocity.y;
        if (t_enter == y1) {
            result.normal = Vec2{0.0f, -1.0f};
        } else {
            result.normal = Vec2{0.0f, 1.0f};
        }
    }

    return result;
}

// 点是否在 AABB 内
inline bool contains(const AABB& aabb, const Vec2& point) {
    return point.x >= aabb.min.x && point.x <= aabb.max.x &&
           point.y >= aabb.min.y && point.y <= aabb.max.y;
}

// 扩展 AABB
inline AABB expanded(const AABB& aabb, f32 amount) {
    return {
        {aabb.min.x - amount, aabb.min.y - amount},
        {aabb.max.x + amount, aabb.max.y + amount}
    };
}

} // namespace aabb
} // namespace pixel
