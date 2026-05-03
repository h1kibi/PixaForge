#pragma once

#include "types.h"

namespace pixel {

// 高精度计时器
class Timer {
public:
    Timer();

    // 重置计时器
    void reset();

    // 获取自上次 reset/tick 以来的秒数
    f32 elapsed() const;

    // 获取并重置（返回 delta time）
    f32 tick();

private:
    i64 m_start;
    i64 m_last;
    i64 m_frequency;
};

// 全局时间管理
namespace time {

// 固定时间步长
constexpr f32 FIXED_DT = 1.0f / 60.0f;

// 获取当前帧的 delta time
f32 delta_time();

// 获取固定时间步的累积器
f32 accumulator();

// 获取游戏运行总时间
f32 total_time();

// 获取当前帧号
u64 frame_count();

// 内部更新（由主循环调用）
void begin_frame(f32 dt);

} // namespace time
} // namespace pixel
