#pragma once

#include "../core/types.h"
#include <string>
#include <string_view>
#include <vector>

namespace pixel {

// 文件系统抽象
class FileSystem {
public:
    virtual ~FileSystem() = default;

    // 读取文件
    virtual std::vector<u8> read_file(std::string_view path) = 0;
    virtual std::string read_text(std::string_view path) = 0;

    // 写入文件
    virtual bool write_file(std::string_view path, std::span<const u8> data) = 0;
    virtual bool write_text(std::string_view path, std::string_view text) = 0;

    // 文件信息
    virtual bool file_exists(std::string_view path) = 0;
    virtual i64 file_size(std::string_view path) = 0;

    // 目录操作
    virtual bool dir_exists(std::string_view path) = 0;
    virtual std::vector<std::string> list_dir(std::string_view path) = 0;

    // 路径
    virtual std::string base_path() = 0;
    virtual std::string pref_path(std::string_view org, std::string_view app) = 0;
};

} // namespace pixel
