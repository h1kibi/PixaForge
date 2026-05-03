#pragma once

#include "../core/types.h"

namespace pixel {

// 游戏手柄按钮
enum class GamepadButton : u8 {
    A, B, X, Y,
    Back, Guide, Start,
    LeftStick, RightStick,
    LeftShoulder, RightShoulder,
    DPadUp, DPadDown, DPadLeft, DPadRight,
    Max
};

// 游戏手柄轴
enum class GamepadAxis : u8 {
    LeftX, LeftY,
    RightX, RightY,
    LeftTrigger, RightTrigger,
    Max
};

// 手柄状态
struct GamepadState {
    bool buttons[static_cast<int>(GamepadButton::Max)] = {};
    f32 axes[static_cast<int>(GamepadAxis::Max)] = {};
    bool connected = false;
};

class GamepadManager {
public:
    virtual ~GamepadManager() = default;

    // 更新状态
    virtual void update() = 0;

    // 查询
    virtual bool is_connected(i32 index) const = 0;
    virtual bool is_button_down(i32 index, GamepadButton button) const = 0;
    virtual bool is_button_pressed(i32 index, GamepadButton button) const = 0;
    virtual f32 get_axis(i32 index, GamepadAxis axis) const = 0;

    // 振动
    virtual void set_rumble(i32 index, f32 low_freq, f32 high_freq, i32 duration_ms) = 0;
};

} // namespace pixel
