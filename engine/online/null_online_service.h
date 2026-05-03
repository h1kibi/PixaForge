#pragma once

#include "online_service.h"

namespace pixel {

// 空实现 - 用于离线模式或未连接时
class NullOnlineService : public IOnlineService {
public:
    NullOnlineService() = default;

    bool is_connected() const override { return false; }
    void connect() override {}
    void disconnect() override {}

    void unlock_achievement(std::string_view id) override {}
    bool is_achievement_unlocked(std::string_view id) const override { return false; }

    void submit_score(std::string_view leaderboard, i64 score) override {}
    void fetch_scores(std::string_view leaderboard,
                      std::function<void(const std::vector<ScoreEntry>&)> callback) override {
        if (callback) callback({});
    }

    void upload_save(const std::vector<u8>& data) override {}
    void download_save(std::function<void(const std::vector<u8>&)> callback) override {
        if (callback) callback({});
    }

    void set_stat(std::string_view name, i64 value) override {}
    i64 get_stat(std::string_view name) const override { return 0; }

    std::string user_name() const override { return "Local Player"; }
    std::string user_id() const override { return "local"; }
};

} // namespace pixel
