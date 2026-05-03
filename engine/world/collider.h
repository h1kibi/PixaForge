#pragma once

#include "../core/types.h"
#include "../core/math.h"

namespace pixel {

// 碰撞结果
struct CollisionResult {
    bool collided = false;
    Vec2 normal = Vec2::zero();
    f32 penetration = 0.0f;
    Vec2 contact_point = Vec2::zero();
};

// 碰撞查询结果
struct RaycastHit {
    bool hit = false;
    Vec2 point = Vec2::zero();
    Vec2 normal = Vec2::zero();
    f32 distance = 0.0f;
    Entity entity = INVALID_ENTITY;
};

} // namespace pixel
