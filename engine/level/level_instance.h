#pragma once

#include "../core/types.h"
#include "level.h"
#include "tilemap.h"
#include "trigger.h"
#include "../collision/tile_collision.h"
#include <memory>

namespace pixel {

// 关卡实例 - 运行时的关卡状态
class LevelInstance {
public:
    LevelInstance() = default;

    // 加载关卡
    bool load(std::string_view path);

    // 重新加载（热重载）
    bool reload();

    // 更新
    void update(f32 dt);

    // 渲染
    void render(class Renderer& renderer, const Camera& camera);

    // 获取 tilemap
    Tilemap& tilemap() { return m_tilemap; }
    const Tilemap& tilemap() const { return m_tilemap; }

    // 获取碰撞层
    TileCollision& collision() { return m_collision; }
    const TileCollision& collision() const { return m_collision; }

    // 获取触发器管理器
    TriggerManager& triggers() { return m_triggers; }

    // 获取关卡数据
    const LevelData& data() const { return m_level_data; }

    // 查找标记点
    Vec2 find_marker(std::string_view name) const;

    // 获取玩家出生点
    Vec2 player_spawn() const { return m_level_data.player_spawn; }

    // 获取摄像机边界
    Rect camera_bounds() const { return m_level_data.camera_bounds; }
    bool has_camera_bounds() const { return m_level_data.use_camera_bounds; }

private:
    LevelData m_level_data;
    Tilemap m_tilemap;
    TileCollision m_collision;
    TriggerManager m_triggers;
    std::unique_ptr<Level> m_level;
};

} // namespace pixel
