#pragma once

#include "../core/types.h"
#include <string>
#include <unordered_map>

namespace pixel {

// 输入缓冲 - 用于实现 jump buffer、coyote time 等
class InputBuffer {
public:
    InputBuffer() = default;

    // 设置缓冲时间（秒）
    void set_buffer_time(f32 seconds) { m_buffer_time = seconds; }

    // 记录输入
    void record(std::string_view action);

    // 检查缓冲中是否有输入
    bool consume(std::string_view action);

    // 更新（每帧调用，清除过期缓冲）
    void update(f32 dt);

    // 清空所有缓冲
    void clear();

private:
    f32 m_buffer_time = 0.1f;  // 默认 100ms 缓冲

    struct BufferedInput {
        std::string action;
        f32 time_remaining;
    };

    std::vector<BufferedInput> m_buffer;
};

// Coyote Time - 离开平台后仍可跳跃的短暂时间
class CoyoteTimer {
public:
    void set_time(f32 seconds) { m_coyote_time = seconds; }

    void update(f32 dt) {
        if (m_timer > 0.0f) {
            m_timer -= dt;
        }
    }

    // 当角色着地时调用
    void on_grounded() {
        m_timer = m_coyote_time;
    }

    // 当角色跳跃时调用
    void on_jump() {
        m_timer = 0.0f;
    }

    // 是否还在 coyote 时间内
    bool can_jump() const {
        return m_timer > 0.0f;
    }

    void reset() { m_timer = 0.0f; }

private:
    f32 m_coyote_time = 0.1f;  // 默认 100ms
    f32 m_timer = 0.0f;
};

} // namespace pixel
