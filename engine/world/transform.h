#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "entity.h"

namespace pixel {

// Transform 组件
struct Transform {
    Vec2 position = Vec2::zero();
    Vec2 scale = Vec2::one();
    f32 rotation = 0.0f;
    Entity parent = INVALID_ENTITY;
};

// Sprite 组件
struct Sprite {
    TextureHandle texture = {};
    Rect source = {};        // 纹理中的区域
    Color color = Color::white();
    i32 layer = 0;           // 绘制层
    bool flip_x = false;
    bool flip_y = false;
    bool visible = true;
};

// Actor 组件（用于有物理行为的实体）
struct Actor {
    Vec2 velocity = Vec2::zero();
    Vec2 acceleration = Vec2::zero();
    f32 gravity_scale = 1.0f;
    bool grounded = false;
    bool active = true;
};

// Collider 组件
struct Collider {
    AABB local_bounds = {};  // 相对于 transform 的边界
    CollisionMask mask = CollisionMask::None;
    CollisionMask layer = CollisionMask::None;
    bool is_trigger = false;  // 是否只触发事件，不产生物理碰撞
    bool enabled = true;
};

// 动画组件
struct Animation {
    TextureHandle spritesheet = {};
    i32 frame_width = 0;
    i32 frame_height = 0;
    i32 current_frame = 0;
    i32 frame_count = 0;
    f32 frame_time = 0.1f;   // 每帧持续时间
    f32 timer = 0.0f;
    bool loop = true;
    bool playing = true;
};

// 标记组件
struct Checkpoint {};
struct Trigger {};
struct Hazard {};
struct Player {};
struct Enemy {};

} // namespace pixel
