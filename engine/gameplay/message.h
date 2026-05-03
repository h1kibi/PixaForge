#pragma once

#include "../core/types.h"
#include <string>
#include <variant>

namespace pixel {

// 消息类型
enum class MessageType : u8 {
    // 游戏事件
    CheckpointReached,
    LevelCompleted,
    PlayerDied,
    EnemyKilled,

    // 物理事件
    CollisionEnter,
    CollisionExit,
    TriggerEnter,
    TriggerExit,

    // 游戏逻辑
    KeyCollected,
    DoorOpened,
    DamageDealt,
    HealthChanged,

    // 自定义
    Custom,
};

// 消息数据
struct Message {
    MessageType type = MessageType::Custom;
    Entity sender = INVALID_ENTITY;
    Entity receiver = INVALID_ENTITY;

    // 消息数据（使用 variant 支持多种类型）
    using Value = std::variant<
        std::monostate,     // 空值
        i32,                // 整数
        f32,                // 浮点数
        bool,               // 布尔
        Vec2,               // 向量
        std::string         // 字符串
    >;

    Value data;
    std::string custom_type;  // 自定义消息类型名

    // 工厂方法
    static Message checkpoint_reached(Entity sender, i32 checkpoint_id) {
        return {MessageType::CheckpointReached, sender, INVALID_ENTITY, checkpoint_id};
    }

    static Message player_died(Entity sender) {
        return {MessageType::PlayerDied, sender, INVALID_ENTITY};
    }

    static Message key_collected(Entity sender, Entity receiver) {
        return {MessageType::KeyCollected, sender, receiver};
    }

    static Message damage(Entity sender, Entity receiver, f32 amount) {
        return {MessageType::DamageDealt, sender, receiver, amount};
    }

    static Message custom(Entity sender, Entity receiver, const std::string& type, Value data = {}) {
        Message msg;
        msg.type = MessageType::Custom;
        msg.sender = sender;
        msg.receiver = receiver;
        msg.custom_type = type;
        msg.data = data;
        return msg;
    }
};

// 消息队列 - 用于实体间通信
class MessageQueue {
public:
    MessageQueue() = default;

    // 发送消息
    void send(const Message& msg) {
        m_queue.push_back(msg);
    }

    // 处理所有消息
    template<typename Handler>
    void process(Handler&& handler) {
        for (const auto& msg : m_queue) {
            handler(msg);
        }
        m_queue.clear();
    }

    // 清空
    void clear() {
        m_queue.clear();
    }

    // 获取队列大小
    size_t size() const { return m_queue.size(); }

private:
    std::vector<Message> m_queue;
};

} // namespace pixel
