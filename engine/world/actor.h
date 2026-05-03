#pragma once

#include "entity.h"

namespace pixel {

// 系统接口 - 处理特定组件的逻辑
class System {
public:
    virtual ~System() = default;

    // 初始化
    virtual void init(class World& world) {}

    // 每帧更新
    virtual void update(World& world, f32 dt) = 0;

    // 固定时间步更新（用于物理）
    virtual void fixed_update(World& world, f32 dt) {}

    // 渲染（可选）
    virtual void render(World& world, class Renderer& renderer) {}
};

} // namespace pixel
