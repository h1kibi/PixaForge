#pragma once

#include "../core/types.h"
#include "../core/math.h"

namespace pixel {

// 像素完美缩放器 - 处理虚拟分辨率到屏幕的缩放
class PixelScaler {
public:
    PixelScaler() = default;

    // 设置虚拟分辨率
    void set_virtual_size(i32 width, i32 height) {
        m_virtual_width = width;
        m_virtual_height = height;
        recalculate();
    }

    // 设置实际屏幕大小
    void set_screen_size(i32 width, i32 height) {
        m_screen_width = width;
        m_screen_height = height;
        recalculate();
    }

    // 获取缩放后的视口（居中显示）
    i32 viewport_x() const { return m_viewport_x; }
    i32 viewport_y() const { return m_viewport_y; }
    i32 viewport_width() const { return m_viewport_width; }
    i32 viewport_height() const { return m_viewport_height; }

    // 整数倍缩放因子
    i32 scale_factor() const { return m_scale; }

    // 屏幕坐标转虚拟坐标
    Vec2 screen_to_virtual(const Vec2& screen_pos) const {
        return {
            (screen_pos.x - m_viewport_x) / m_scale,
            (screen_pos.y - m_viewport_y) / m_scale
        };
    }

    // 虚拟坐标转屏幕坐标
    Vec2 virtual_to_screen(const Vec2& virtual_pos) const {
        return {
            virtual_pos.x * m_scale + m_viewport_x,
            virtual_pos.y * m_scale + m_viewport_y
        };
    }

private:
    void recalculate() {
        if (m_virtual_width <= 0 || m_virtual_height <= 0 ||
            m_screen_width <= 0 || m_screen_height <= 0) {
            m_scale = 1;
            m_viewport_x = 0;
            m_viewport_y = 0;
            m_viewport_width = m_screen_width;
            m_viewport_height = m_screen_height;
            return;
        }

        // 计算最大整数倍缩放
        i32 scale_x = m_screen_width / m_virtual_width;
        i32 scale_y = m_screen_height / m_virtual_height;
        m_scale = (std::max)(1, (std::min)(scale_x, scale_y));

        // 计算居中视口
        m_viewport_width = m_virtual_width * m_scale;
        m_viewport_height = m_virtual_height * m_scale;
        m_viewport_x = (m_screen_width - m_viewport_width) / 2;
        m_viewport_y = (m_screen_height - m_viewport_height) / 2;
    }

    i32 m_virtual_width = 320;
    i32 m_virtual_height = 180;
    i32 m_screen_width = 1280;
    i32 m_screen_height = 720;
    i32 m_scale = 1;
    i32 m_viewport_x = 0;
    i32 m_viewport_y = 0;
    i32 m_viewport_width = 1280;
    i32 m_viewport_height = 720;
};

} // namespace pixel
