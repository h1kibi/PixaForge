#pragma once

#include "behavior.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <functional>
#include <memory>

namespace pixel {

// 行为注册表 - 管理所有行为类型
class BehaviorRegistry {
public:
    static BehaviorRegistry& instance() {
        static BehaviorRegistry s_instance;
        return s_instance;
    }

    // 注册行为
    using BehaviorFactory = std::function<std::unique_ptr<Behavior>()>;

    void register_behavior(std::string_view name, BehaviorFactory factory) {
        m_factories[std::string(name)] = std::move(factory);
    }

    // 创建行为实例
    std::unique_ptr<Behavior> create(std::string_view name) const {
        auto it = m_factories.find(std::string(name));
        if (it != m_factories.end()) {
            return it->second();
        }
        return nullptr;
    }

    // 检查是否存在
    bool has(std::string_view name) const {
        return m_factories.find(std::string(name)) != m_factories.end();
    }

    // 获取所有注册的行为名
    std::vector<std::string> list_behaviors() const {
        std::vector<std::string> result;
        for (const auto& [name, factory] : m_factories) {
            result.push_back(name);
        }
        return result;
    }

private:
    BehaviorRegistry() = default;
    std::unordered_map<std::string, BehaviorFactory> m_factories;
};

} // namespace pixel
