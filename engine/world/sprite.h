#pragma once

#include "core/types.h"
#include "renderer/texture.h"
#include "renderer/color.h"

namespace pf {

struct Sprite {
    TextureHandle texture = {};
    Rect source = {};        // 纹理中的区域
    Color color = {255, 255, 255, 255};
    int layer = 0;           // 绘制层
    bool flip_x = false;
    bool flip_y = false;
    bool visible = true;
};

}
