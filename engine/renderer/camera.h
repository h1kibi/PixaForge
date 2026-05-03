#pragma once

#include "../core/math.h"

namespace pixel {

// 摄像机 - 控制视口
struct Camera {
    Vec2 position = Vec2::zero();  // 世界坐标中的位置（左上角）
    f32 zoom = 1.0f;
    f32 rotation = 0.0f;

    // 跟踪目标
    Vec2 target = Vec2::zero();
    f32 smooth_speed = 0.1f;  // 平滑跟随速度

    // 边界限制
    Rect bounds = {};  // 世界边界
    bool use_bounds = false;

    // Pixel-perfect 设置
    bool pixel_perfect = true;  // 像素对齐

    // 更新摄像机（平滑跟随）
    void update(f32 dt) {
        position.x = math::lerp(position.x, target.x, smooth_speed);
        position.y = math::lerp(position.y, target.y, smooth_speed);

        if (pixel_perfect) {
            position.x = math::round(position.x);
            position.y = math::round(position.y);
        }

        if (use_bounds) {
            position.x = math::clamp(position.x, bounds.x, bounds.x + bounds.w);
            position.y = math::clamp(position.y, bounds.y, bounds.y + bounds.h);
        }
    }

    // 获取视口矩形
    Rect viewport(i32 screen_width, i32 screen_height) const {
        f32 w = screen_width / zoom;
        f32 h = screen_height / zoom;
        return {position.x, position.y, w, h};
    }

    // 世界坐标转屏幕坐标
    Vec2 world_to_screen(const Vec2& world_pos, i32 screen_width, i32 screen_height) const {
        return {
            (world_pos.x - position.x) * zoom,
            (world_pos.y - position.y) * zoom
        };
    }

    // 屏幕坐标转世界坐标
    Vec2 screen_to_world(const Vec2& screen_pos) const {
        return {
            screen_pos.x / zoom + position.x,
            screen_pos.y / zoom + position.y
        };
    }

    // 设置跟随目标
    void look_at(const Vec2& pos) {
        target = pos;
    }

    // 立即设置位置（无平滑）
    void snap_to(const Vec2& pos) {
        position = pos;
        target = pos;
    }
};

} // namespace pixel
