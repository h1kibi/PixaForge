#pragma once

#include "types.h"
#include <string>
#include <string_view>
#include <vector>
#include <span>

namespace pixel {

// 简单的字符串 ID（用于快速比较）
struct StringID {
    u32 hash = 0;

    StringID() = default;
    explicit StringID(std::string_view str);

    bool operator==(const StringID& other) const = default;
    bool is_valid() const { return hash != 0; }

    static u32 compute_hash(std::string_view str);
};

// 文件操作
namespace file {

// 读取整个文件到字节数组
std::vector<u8> read_bytes(std::string_view path);

// 读取整个文件到字符串
std::string read_text(std::string_view path);

// 写入字节数组到文件
bool write_bytes(std::string_view path, std::span<const u8> data);

// 写入字符串到文件
bool write_text(std::string_view path, std::string_view text);

// 检查文件是否存在
bool exists(std::string_view path);

// 获取文件大小
i64 size(std::string_view path);

// 路径工具
std::string normalize(std::string_view path);
std::string extension(std::string_view path);
std::string filename(std::string_view path);
std::string directory(std::string_view path);
std::string join(std::string_view a, std::string_view b);

} // namespace file
} // namespace pixel
