#pragma once

#include "../core/types.h"
#include "../renderer/texture.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>

namespace pixel {

// 资源类型
enum class AssetType : u8 {
    Texture,
    Sound,
    Music,
    Animation,
    Level,
    Font,
};

// 资源管理器
class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    // 初始化
    bool init(class Renderer* renderer);
    void shutdown();

    // 纹理管理
    TextureHandle load_texture(std::string_view path);
    void unload_texture(std::string_view path);
    TextureHandle get_texture(std::string_view path) const;

    // 音频管理
    SoundHandle load_sound(std::string_view path);
    void unload_sound(std::string_view path);
    MusicHandle load_music(std::string_view path);
    void unload_music(std::string_view path);

    // 热重载
    void reload_all();
    void reload_texture(std::string_view path);

    // 清空所有资源
    void clear();

    // 统计
    size_t texture_count() const { return m_textures.size(); }
    size_t sound_count() const { return m_sounds.size(); }

private:
    Renderer* m_renderer = nullptr;

    struct TextureEntry {
        TextureHandle handle;
        std::string path;
        i32 ref_count = 0;
    };

    struct AudioEntry {
        SoundHandle handle;
        std::string path;
        i32 ref_count = 0;
    };

    std::unordered_map<std::string, TextureEntry> m_textures;
    std::unordered_map<std::string, AudioEntry> m_sounds;
    std::unordered_map<std::string, AudioEntry> m_music;
};

} // namespace pixel
