set(ENGINE_SOURCES
    core/version.cpp

    core/types.h
    core/math.h
    core/log.h
    core/assert.h
    core/time.h
    core/handle.h
    core/version.h

    platform/window.h
    platform/filesystem.h
    platform/gamepad.h

    renderer/color.h
    renderer/texture.h
    renderer/renderer.h
    renderer/graphics_device.h
    renderer/sprite_batch.h
    renderer/tilemap_renderer.h
    renderer/camera.h
    renderer/pixel_scaler.h
    renderer/backends/sdl_renderer_backend.h
    renderer/backends/sdl_renderer_backend.cpp

    input/input.h
    input/action.h
    input/input_map.h
    input/input_buffer.h

    world/entity.h
    world/world.h
    world/component_pool.h
    world/transform.h
    world/sprite.h
    world/actor.h
    world/collider.h

    collision/aabb.h
    collision/tile_collision.h
    collision/collision_world.h
    collision/debug_draw.h

    level/level.h
    level/tilemap.h
    level/ldtk_loader.h
    level/trigger.h
    level/level_instance.h

    gameplay/behavior.h
    gameplay/behavior_registry.h
    gameplay/message.h

    assets/asset_manager.h
    assets/texture_loader.h
    assets/animation_loader.h
    assets/asset_pack.h

    online/online_service.h
    online/null_online_service.h
)

find_package(SDL3 CONFIG REQUIRED)

add_library(pixaforge STATIC ${ENGINE_SOURCES})

target_include_directories(pixaforge
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(pixaforge PUBLIC cxx_std_20)

target_link_libraries(pixaforge
    PUBLIC
        SDL3::SDL3
)

target_compile_definitions(pixaforge
    PUBLIC
        PF_PLATFORM_SDL3=1
        PF_RENDERER_SDL=1
)
