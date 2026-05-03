#pragma once

#include "../core/types.h"
#include "../core/math.h"

namespace pixel {

struct Transform;
struct Sprite;
struct Actor;
struct Collider;
struct Animation;

// 组件池 - 存储特定类型组件
template<typename T>
class ComponentPool {
public:
    ComponentPool() = default;

    // 分配组件
    T& add(Entity entity) {
        // 简化实现：使用 entity.index 作为索引
        if (entity.index >= m_data.size()) {
            m_data.resize(entity.index + 1);
        }
        m_data[entity.index] = T{};
        return m_data[entity.index];
    }

    // 获取组件
    T* get(Entity entity) {
        if (entity.index >= m_data.size()) {
            return nullptr;
        }
        return &m_data[entity.index];
    }

    const T* get(Entity entity) const {
        if (entity.index >= m_data.size()) {
            return nullptr;
        }
        return &m_data[entity.index];
    }

    // 移除组件
    void remove(Entity entity) {
        if (entity.index < m_data.size()) {
            m_data[entity.index] = T{};
        }
    }

    // 检查是否有组件
    bool has(Entity entity) const {
        // 简化实现：假设非默认值表示有组件
        if (entity.index >= m_data.size()) {
            return false;
        }
        // 这里需要根据实际类型判断，简化为总是返回 true
        return true;
    }

    // 清空
    void clear() {
        m_data.clear();
    }

    // 获取所有数据
    std::span<T> data() { return m_data; }
    std::span<const T> data() const { return m_data; }

private:
    std::vector<T> m_data;
};

} // namespace pixel
