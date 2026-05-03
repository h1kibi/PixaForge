#pragma once

#include "../core/types.h"

namespace pixel {

// 纹理格式
enum class TextureFormat : u8 {
    RGBA8,
    RGB8,
    A8,
    // 可扩展
};

// 纹理创建信息
struct TextureDesc {
    i32 width = 0;
    i32 height = 0;
    TextureFormat format = TextureFormat::RGBA8;
    bool render_target = false;
};

// 纹理接口
class Texture {
public:
    virtual ~Texture() = default;

    virtual i32 width() const = 0;
    virtual i32 height() const = 0;
    virtual TextureHandle handle() const = 0;
};

} // namespace pixel
