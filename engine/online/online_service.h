#pragma once

#include "../core/types.h"
#include <string>
#include <string_view>
#include <functional>

namespace pixel {

// 在线服务接口
class IOnlineService {
public:
    virtual ~IOnlineService() = default;

    // 连接状态
    virtual bool is_connected() const = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;

    // 成就系统
    virtual void unlock_achievement(std::string_view id) = 0;
    virtual bool is_achievement_unlocked(std::string_view id) const = 0;

    // 排行榜
    virtual void submit_score(std::string_view leaderboard, i64 score) = 0;
    virtual void fetch_scores(std::string_view leaderboard,
                              std::function<void(const std::vector<struct ScoreEntry>&)> callback) = 0;

    // 云存档
    virtual void upload_save(const std::vector<u8>& data) = 0;
    virtual void download_save(std::function<void(const std::vector<u8>&)> callback) = 0;

    // 统计
    virtual void set_stat(std::string_view name, i64 value) = 0;
    virtual i64 get_stat(std::string_view name) const = 0;

    // 用户信息
    virtual std::string user_name() const = 0;
    virtual std::string user_id() const = 0;
};

// 排行榜条目
struct ScoreEntry {
    std::string user_name;
    std::string user_id;
    i64 score = 0;
    i32 rank = 0;
};

} // namespace pixel
