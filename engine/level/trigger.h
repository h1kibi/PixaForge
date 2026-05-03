#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include "../world/entity.h"
#include <string>
#include <functional>

namespace pixel {

// 触发器类型
enum class TriggerType : u8 {
    Checkpoint,
    Door,
    Key,
    Hazard,
    LevelEnd,
    Custom,
};

// 触发器数据
struct Trigger {
    std::string name;
    TriggerType type = TriggerType::Custom;
    Rect bounds = {};
    bool active = true;
    bool triggered = false;

    // 关联实体（用于门、钥匙等）
    Entity linked_entity = INVALID_ENTITY;

    // 自定义属性
    std::unordered_map<std::string, std::string> properties;

    // 触发回调
    std::function<void(Entity trigger, Entity other)> on_trigger;
};

// 触发器管理器
class TriggerManager {
public:
    TriggerManager() = default;

    // 添加触发器
    Trigger& add_trigger(const std::string& name, TriggerType type, const Rect& bounds);

    // 移除触发器
    void remove_trigger(const std::string& name);

    // 获取触发器
    Trigger* get_trigger(const std::string& name);

    // 检查实体是否触发任何触发器
    void check_triggers(Entity entity, const AABB& bounds);

    // 更新所有触发器
    void update(f32 dt);

    // 清空
    void clear();

private:
    std::vector<Trigger> m_triggers;
};

} // namespace pixel
