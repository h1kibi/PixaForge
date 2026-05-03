#pragma once

#include "../core/types.h"
#include "level.h"
#include <string_view>

namespace pixel {

// LDtk 关卡加载器
class LDTkLoader {
public:
    LDTkLoader() = default;

    // 加载 LDtk 文件
    bool load(std::string_view path, LevelData& level_data);

    // 热重载
    bool reload(LevelData& level_data);

    // 获取最后加载的文件路径
    std::string_view current_path() const { return m_current_path; }

private:
    // 解析 JSON 数据
    bool parse_json(std::string_view json, LevelData& level_data);

    // 解析 tile 层
    bool parse_tile_layer(std::string_view json, LevelData& level_data);

    // 解析实体层
    bool parse_entity_layer(std::string_view json, LevelData& level_data);

    // 解析触发器
    bool parse_triggers(std::string_view json, LevelData& level_data);

    std::string m_current_path;
};

// Tiled 关卡加载器（后续兼容）
class TiledLoader {
public:
    TiledLoader() = default;

    bool load(std::string_view path, LevelData& level_data);
    bool reload(LevelData& level_data);

private:
    std::string m_current_path;
};

} // namespace pixel
