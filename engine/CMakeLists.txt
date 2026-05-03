set(ENGINE_SOURCES
    # Core
    core/types.h
    core/math.h
    core/log.h
    core/assert.h
    core/time.h
    core/handle.h

    # Platform
    platform/window.h
    platform/filesystem.h
    platform/gamepad.h

    # Renderer
    renderer/renderer.h
    renderer/graphics_device.h
    renderer/texture.h
    renderer/sprite_batch.h
    renderer/tilemap_renderer.h
    renderer/camera.h
    renderer/pixel_scaler.h

    # Input
    input/input.h
    input/action.h
    input/input_map.h
    input/input_buffer.h

    # World
    world/entity.h
    world/world.h
    world/component_pool.h
    world/transform.h
    world/sprite.h
    world/actor.h
    world/collider.h

    # Collision
    collision/aabb.h
    collision/tile_collision.h
    collision/collision_world.h
    collision/debug_draw.h

    # Level
    level/level.h
    level/tilemap.h
    level/ldtk_loader.h
    level/trigger.h
    level/level_instance.h

    # Gameplay
    gameplay/behavior.h
    gameplay/behavior_registry.h
    gameplay/message.h

    # Assets
    assets/asset_manager.h
    assets/texture_loader.h
    assets/animation_loader.h
    assets/asset_pack.h

    # Online
    online/online_service.h
    online/null_online_service.h
)

add_library(engine STATIC ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# SDL3 依赖（需要手动下载或通过 vcpkg/conan 安装）
# find_package(SDL3 REQUIRED)
# target_link_libraries(engine PUBLIC SDL3::SDL3)

# 临时：设置编译定义，后续替换为实际 SDL 链接
target_compile_definitions(engine PUBLIC
    PLATFORM_SDL3=1
    RENDERER_OPENGL=1
)
