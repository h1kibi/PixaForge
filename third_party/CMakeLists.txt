# 第三方库配置
# 
# SDL3 安装方式（选择一种）：
# 1. vcpkg: vcpkg install sdl3
# 2. conan: conan install sdl3/3.x.x@
# 3. 手动下载: https://github.com/libsdl-org/SDL/releases
#
# Dear ImGui（调试 UI）：
# 1. 手动克隆: git clone https://github.com/ocornut/imgui.git
# 2. vcpkg: vcpkg install imgui

# 示例：使用 vcpkg 时
# find_package(SDL3 REQUIRED)
# find_package(imgui REQUIRED)

# 手动 SDL3 配置（如果不用包管理器）
# set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL3")
# add_subdirectory(SDL3)

# 手动 ImGui 配置
# set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
# add_library(imgui STATIC
#     ${IMGUI_DIR}/imgui.cpp
#     ${IMGUI_DIR}/imgui_demo.cpp
#     ${IMGUI_DIR}/imgui_draw.cpp
#     ${IMGUI_DIR}/imgui_tables.cpp
#     ${IMGUI_DIR}/imgui_widgets.cpp
#     ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
#     ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
# )
# target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
