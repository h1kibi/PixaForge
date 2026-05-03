#pragma once

#include "../core/types.h"
#include <string_view>
#include <unordered_map>

namespace pixel {

// 输入动作类型
enum class ActionType : u8 {
    Button,     // 按下/松开
    Axis,       // 轴值 (-1 到 1)
};

// 输入动作定义
struct Action {
    std::string_view name;
    ActionType type = ActionType::Button;
};

// 输入系统接口
class Input {
public:
    virtual ~Input() = default;

    // 帧更新
    virtual void begin_frame() = 0;
    virtual void end_frame() = 0;

    // 按钮查询
    virtual bool pressed(std::string_view action) const = 0;   // 刚按下
    virtual bool released(std::string_view action) const = 0;  // 刚松开
    virtual bool down(std::string_view action) const = 0;      // 持续按住
    virtual bool up(std::string_view action) const = 0;        // 持续松开

    // 轴查询
    virtual f32 axis(std::string_view action) const = 0;

    // 原始输入查询（用于调试）
    virtual bool key_down(i32 keycode) const = 0;
    virtual bool mouse_button_down(i32 button) const = 0;
    virtual Vec2 mouse_position() const = 0;

    // 手柄
    virtual bool gamepad_button_down(i32 index, i32 button) const = 0;
    virtual f32 gamepad_axis(i32 index, i32 axis) const = 0;
};

} // namespace pixel
