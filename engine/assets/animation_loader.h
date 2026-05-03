#pragma once

#include "../core/types.h"
#include "../renderer/texture.h"
#include <string>
#include <vector>

namespace pixel {

// 动画帧
struct AnimationFrame {
    i32 x, y;          // 纹理中的位置
    i32 width, height; // 帧大小
    f32 duration;      // 持续时间（秒）
};

// 动画定义
struct AnimationDef {
    std::string name;
    std::vector<AnimationFrame> frames;
    bool loop = true;
};

// 动画加载器
class AnimationLoader {
public:
    AnimationLoader() = default;

    // 从 JSON 加载动画定义
    static bool load_from_json(std::string_view path,
                               std::vector<AnimationDef>& animations);

    // 从 spritesheet 加载（等间距帧）
    static bool load_from_spritesheet(std::string_view name,
                                      i32 frame_width, i32 frame_height,
                                      i32 frame_count, f32 frame_duration,
                                      AnimationDef& animation);

    // 保存动画定义到 JSON
    static bool save_to_json(std::string_view path,
                             const std::vector<AnimationDef>& animations);
};

} // namespace pixel
