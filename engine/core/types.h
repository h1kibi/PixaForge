#pragma once

#include <cstdint>
#include <cstddef>
#include <string_view>

namespace pixel {

// 基础类型别名
using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

// Entity ID
struct EntityID {
    u32 index = 0;
    u32 generation = 0;

    bool operator==(const EntityID& other) const = default;
    bool is_valid() const { return index != 0; }
};

// Handle 类型（用于纹理、音频等资源）
template<typename Tag>
struct Handle {
    u32 id = 0;

    bool is_valid() const { return id != 0; }
    bool operator==(const Handle& other) const = default;
};

// 资源 Handle 类型
using TextureHandle = Handle<struct TextureTag>;
using SoundHandle   = Handle<struct SoundTag>;
using MusicHandle   = Handle<struct MusicTag>;

// 碰撞掩码
enum class CollisionMask : u32 {
    None      = 0,
    Player    = 1 << 0,
    Enemy     = 1 << 1,
    Platform  = 1 << 2,
    Trigger   = 1 << 3,
    Hazard    = 1 << 4,
    All       = 0xFFFFFFFF
};

inline CollisionMask operator|(CollisionMask a, CollisionMask b) {
    return static_cast<CollisionMask>(
        static_cast<u32>(a) | static_cast<u32>(b)
    );
}

inline CollisionMask operator&(CollisionMask a, CollisionMask b) {
    return static_cast<CollisionMask>(
        static_cast<u32>(a) & static_cast<u32>(b)
    );
}

} // namespace pixel
