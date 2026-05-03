#pragma once

#include "types.h"
#include <cmath>
#include <algorithm>

namespace pixel {

struct Vec2 {
    f32 x = 0.0f;
    f32 y = 0.0f;

    Vec2() = default;
    constexpr Vec2(f32 x, f32 y) : x(x), y(y) {}

    // 基础运算
    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(f32 s) const { return {x * s, y * s}; }
    Vec2 operator/(f32 s) const { return {x / s, y / s}; }

    Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    Vec2& operator*=(f32 s) { x *= s; y *= s; return *this; }

    bool operator==(const Vec2& v) const = default;

    // 工具函数
    f32 length() const { return std::sqrt(x * x + y * y); }
    f32 length_sq() const { return x * x + y * y; }

    Vec2 normalized() const {
        f32 len = length();
        if (len < 1e-6f) return {0.0f, 0.0f};
        return {x / len, y / len};
    }

    f32 dot(const Vec2& v) const { return x * v.x + y * v.y; }

    // 静态工厂
    static constexpr Vec2 zero() { return {0.0f, 0.0f}; }
    static constexpr Vec2 one() { return {1.0f, 1.0f}; }
    static constexpr Vec2 up() { return {0.0f, -1.0f}; }
    static constexpr Vec2 down() { return {0.0f, 1.0f}; }
    static constexpr Vec2 left() { return {-1.0f, 0.0f}; }
    static constexpr Vec2 right() { return {1.0f, 0.0f}; }
};

// 矩形
struct Rect {
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 w = 0.0f;
    f32 h = 0.0f;

    Rect() = default;
    constexpr Rect(f32 x, f32 y, f32 w, f32 h) : x(x), y(y), w(w), h(h) {}

    f32 left() const { return x; }
    f32 right() const { return x + w; }
    f32 top() const { return y; }
    f32 bottom() const { return y + h; }

    Vec2 position() const { return {x, y}; }
    Vec2 size() const { return {w, h}; }
    Vec2 center() const { return {x + w * 0.5f, y + h * 0.5f}; }

    bool contains(const Vec2& point) const {
        return point.x >= x && point.x <= x + w &&
               point.y >= y && point.y <= y + h;
    }

    bool overlaps(const Rect& other) const {
        return x < other.x + other.w && x + w > other.x &&
               y < other.y + other.h && y + h > other.y;
    }
};

// 整数矩形（用于 sprite source rect）
struct IRect {
    i32 x = 0;
    i32 y = 0;
    i32 w = 0;
    i32 h = 0;

    IRect() = default;
    constexpr IRect(i32 x, i32 y, i32 w, i32 h) : x(x), y(y), w(w), h(h) {}
};

// AABB（轴对齐包围盒）
struct AABB {
    Vec2 min;
    Vec2 max;

    AABB() = default;
    constexpr AABB(const Vec2& min, const Vec2& max) : min(min), max(max) {}
    constexpr AABB(f32 x, f32 y, f32 w, f32 h) : min{x, y}, max{x + w, y + h} {}

    f32 width() const { return max.x - min.x; }
    f32 height() const { return max.y - min.y; }
    Vec2 center() const { return {(min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f}; }
    Vec2 size() const { return {width(), height()}; }

    bool overlaps(const AABB& other) const {
        return min.x < other.max.x && max.x > other.min.x &&
               min.y < other.max.y && max.y > other.min.y;
    }

    bool contains(const Vec2& point) const {
        return point.x >= min.x && point.x <= max.x &&
               point.y >= min.y && point.y <= max.y;
    }

    // 移动后的 AABB
    AABB moved(const Vec2& offset) const {
        return {min + offset, max + offset};
    }
};

// 数学工具
namespace math {

constexpr f32 PI = 3.14159265358979323846f;

inline f32 abs(f32 x) { return std::abs(x); }
inline f32 floor(f32 x) { return std::floor(x); }
inline f32 ceil(f32 x) { return std::ceil(x); }
inline f32 round(f32 x) { return std::round(x); }
inline f32 sqrt(f32 x) { return std::sqrt(x); }

template<typename T>
T clamp(T value, T min, T max) {
    return std::clamp(value, min, max);
}

inline f32 lerp(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

inline f32 sign(f32 x) {
    return x > 0.0f ? 1.0f : (x < 0.0f ? -1.0f : 0.0f);
}

inline f32 deg_to_rad(f32 deg) {
    return deg * PI / 180.0f;
}

inline f32 rad_to_deg(f32 rad) {
    return rad * 180.0f / PI;
}

} // namespace math
} // namespace pixel
