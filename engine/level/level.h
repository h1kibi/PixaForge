#pragma once

#include "../core/types.h"
#include "../core/math.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace pixel {

// 关卡数据
struct LevelData {
    std::string name;
    i32 width = 0;      // tile 数量
    i32 height = 0;
    i32 tile_width = 16;
    i32 tile_height = 16;

    // 图层数据
    std::vector<i32> background_tiles;
    std::vector<i32> foreground_tiles;
    std::vector<i32> collision_tiles;

    // 实体生成点
    struct SpawnPoint {
        std::string type;    // "player", "enemy_slime", etc.
        Vec2 position;
        std::unordered_map<std::string, std::string> properties;
    };
    std::vector<SpawnPoint> spawn_points;

    // 触发器
    struct TriggerData {
        std::string name;
        Rect bounds;
        std::string action;  // "checkpoint", "door", "key", etc.
        std::unordered_map<std::string, std::string> properties;
    };
    std::vector<TriggerData> triggers;

    // 摄像机边界
    Rect camera_bounds = {};
    bool use_camera_bounds = false;

    // 玩家出生点
    Vec2 player_spawn = Vec2::zero();
};

// 关卡接口
class Level {
public:
    virtual ~Level() = default;

    // 加载关卡
    virtual bool load(std::string_view path) = 0;

    // 获取关卡数据
    virtual const LevelData& data() const = 0;

    // 重新加载（热重载）
    virtual bool reload() = 0;

    // 获取标记点位置
    virtual Vec2 find_marker(std::string_view name) const = 0;
};

} // namespace pixel
