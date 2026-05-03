#pragma once

#include "../core/types.h"
#include "action.h"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

namespace pixel {

// 输入映射 - 将物理输入映射到动作
class InputMap {
public:
    InputMap() = default;

    // 注册动作
    void register_action(std::string_view name, ActionType type);

    // 绑定键盘
    void bind_key(std::string_view action, KeyCode key);

    // 绑定鼠标
    void bind_mouse(std::string_view action, MouseButton button);

    // 绑定手柄按钮
    void bind_gamepad_button(std::string_view action, i32 gamepad_index, i32 button);

    // 绑定手柄轴
    void bind_gamepad_axis(std::string_view action, i32 gamepad_index, i32 axis, bool positive);

    // 查询绑定
    struct Binding {
        enum class Type { Key, MouseButton, GamepadButton, GamepadAxis } type;
        KeyCode key = KeyCode::Unknown;
        MouseButton mouse_btn = MouseButton::Left;
        i32 gamepad_index = 0;
        i32 gamepad_btn = 0;
        i32 gamepad_axis = 0;
        bool axis_positive = true;
    };

    const std::vector<Binding>& get_bindings(std::string_view action) const;
    bool has_action(std::string_view action) const;
    ActionType get_action_type(std::string_view action) const;

private:
    struct ActionDef {
        std::string name;
        ActionType type;
        std::vector<Binding> bindings;
    };

    std::vector<ActionDef> m_actions;
    std::unordered_map<std::string_view, size_t> m_action_map;
};

} // namespace pixel
