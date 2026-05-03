#pragma once

#include "../core/types.h"

namespace pixel {

// Entity 结构 - 使用 generation 避免 ABA 问题
struct Entity {
    u32 index = 0;
    u32 generation = 0;

    bool is_valid() const { return index != 0; }
    bool operator==(const Entity& other) const = default;
};

// 无效 Entity 常量
constexpr Entity INVALID_ENTITY = {0, 0};

} // namespace pixel
