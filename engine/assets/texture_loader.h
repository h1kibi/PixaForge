#pragma once

#include "../core/types.h"
#include "../renderer/texture.h"
#include <string_view>

namespace pixel {

// 纹理加载器
class TextureLoader {
public:
    TextureLoader() = default;

    // 加载纹理
    static TextureHandle load(class Renderer& renderer, std::string_view path);

    // 从内存加载
    static TextureHandle load_from_memory(class Renderer& renderer,
                                          const u8* data, i32 width, i32 height);

    // 创建空白纹理
    static TextureHandle create_blank(class Renderer& renderer, i32 width, i32 height);

    // 保存纹理到文件
    static bool save_to_file(TextureHandle texture, std::string_view path);
};

} // namespace pixel
