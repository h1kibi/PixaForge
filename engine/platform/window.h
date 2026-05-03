#pragma once

#include "../core/types.h"
#include <string_view>

namespace pixel {

struct WindowDesc {
    std::string_view title = "Pixel Engine";
    i32 width = 1280;
    i32 height = 720;
    bool fullscreen = false;
    bool vsync = true;
    bool resizable = true;
};

class Window {
public:
    Window() = default;
    virtual ~Window() = default;

    // 禁止拷贝
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    virtual bool create(const WindowDesc& desc) = 0;
    virtual void destroy() = 0;

    virtual void poll_events() = 0;
    virtual bool should_close() const = 0;

    // 尺寸
    virtual i32 width() const = 0;
    virtual i32 height() const = 0;
    virtual f32 aspect_ratio() const = 0;

    // 全屏
    virtual void set_fullscreen(bool fullscreen) = 0;
    virtual bool is_fullscreen() const = 0;

    // 标题
    virtual void set_title(std::string_view title) = 0;

    // 原生句柄（SDL_Window*, HWND 等）
    virtual void* native_handle() = 0;
};

} // namespace pixel
