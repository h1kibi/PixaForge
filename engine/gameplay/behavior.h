#pragma once

#include "../world/entity.h"

namespace pixel {

// 行为接口 - 所有游戏逻辑的基础
class Behavior {
public:
    virtual ~Behavior() = default;

    // 生命周期回调
    virtual void on_create(Entity self) {}
    virtual void on_destroy(Entity self) {}

    // 每帧更新
    virtual void on_update(Entity self, f32 dt) = 0;

    // 固定时间步更新（用于物理）
    virtual void on_fixed_update(Entity self, f32 dt) {}

    // 碰撞回调
    virtual void on_collision(Entity self, Entity other) {}

    // 触发器回调
    virtual void on_trigger(Entity self, Entity other) {}

    // 消息回调
    virtual void on_message(Entity self, const struct Message& msg) {}
};

// 行为注册宏
#define REGISTER_BEHAVIOR(name, class_name) \
    static struct class_name##_Registrar { \
        class_name##_Registrar() { \
            ::pixel::BehaviorRegistry::instance().register_behavior(name, \
                []() -> std::unique_ptr<::pixel::Behavior> { \
                    return std::make_unique<class_name>(); \
                }); \
        } \
    } s_##class_name##_registrar;

} // namespace pixel
