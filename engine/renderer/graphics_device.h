#pragma once

#include "../core/types.h"
#include <string_view>

namespace pixel {

// 图形设备接口（抽象底层 API）
class GraphicsDevice {
public:
    virtual ~GraphicsDevice() = default;

    virtual bool init(void* window_handle) = 0;
    virtual void shutdown() = 0;

    virtual void present() = 0;
    virtual void clear(u8 r, u8 g, u8 b, u8 a) = 0;

    virtual void set_viewport(i32 x, i32 y, i32 w, i32 h) = 0;

    // 创建渲染目标（用于虚拟分辨率）
    virtual TextureHandle create_render_target(i32 width, i32 height) = 0;
    virtual void destroy_render_target(TextureHandle handle) = 0;
    virtual void set_render_target(TextureHandle handle) = 0;
    virtual void reset_render_target() = 0;
};

} // namespace pixel
