#pragma once

#include "../core/types.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace pixel {

// Asset Pack 文件格式
// 简单的打包格式，用于发布版本
//
// 文件结构：
// [Header]
//   magic: "PEPK" (4 bytes)
//   version: u32
//   file_count: u32
// [File Table]
//   for each file:
//     name_hash: u64
//     offset: u32
//     size: u32
//     type: u8
// [File Data]
//   raw file data

struct PackHeader {
    char magic[4] = {'P', 'E', 'P', 'K'};
    u32 version = 1;
    u32 file_count = 0;
};

struct PackFileEntry {
    u64 name_hash = 0;
    u32 offset = 0;
    u32 size = 0;
    AssetType type = AssetType::Texture;
};

// Asset Pack 管理器
class AssetPack {
public:
    AssetPack() = default;

    // 加载 pack 文件
    bool load(std::string_view path);

    // 创建 pack 文件（从目录）
    static bool create(std::string_view source_dir, std::string_view output_path);

    // 从 pack 中读取文件
    bool read_file(std::string_view name, std::vector<u8>& data) const;

    // 查询文件信息
    bool has_file(std::string_view name) const;
    size_t file_size(std::string_view name) const;

    // 获取所有文件名
    std::vector<std::string> list_files() const;

private:
    std::vector<u8> m_data;
    std::vector<PackFileEntry> m_entries;
    std::unordered_map<std::string, size_t> m_name_map;
};

} // namespace pixel
