#pragma once

#include "../core/types.h"
#include "entity.h"
#include "component_pool.h"
#include "transform.h"
#include "../renderer/renderer.h"
#include <vector>
#include <functional>

namespace pixel {

// 世界 - 管理所有实体和组件
class World {
public:
    World() = default;

    // 创建实体
    Entity create_entity() {
        Entity entity;
        entity.index = ++m_next_entity_id;
        entity.generation = 0;
        m_entities.push_back(entity);
        return entity;
    }

    // 销毁实体
    void destroy_entity(Entity entity) {
        // 简化实现：标记为无效
        // 实际应用中需要更复杂的回收机制
    }

    // 获取组件
    template<typename T>
    T* get_component(Entity entity) {
        if constexpr (std::is_same_v<T, Transform>) {
            return m_transforms.get(entity);
        } else if constexpr (std::is_same_v<T, Sprite>) {
            return m_sprites.get(entity);
        } else if constexpr (std::is_same_v<T, Actor>) {
            return m_actors.get(entity);
        } else if constexpr (std::is_same_v<T, Collider>) {
            return m_colliders.get(entity);
        } else if constexpr (std::is_same_v<T, Animation>) {
            return m_animations.get(entity);
        }
        return nullptr;
    }

    // 添加组件
    template<typename T>
    T& add_component(Entity entity) {
        if constexpr (std::is_same_v<T, Transform>) {
            return m_transforms.add(entity);
        } else if constexpr (std::is_same_v<T, Sprite>) {
            return m_sprites.add(entity);
        } else if constexpr (std::is_same_v<T, Actor>) {
            return m_actors.add(entity);
        } else if constexpr (std::is_same_v<T, Collider>) {
            return m_colliders.add(entity);
        } else if constexpr (std::is_same_v<T, Animation>) {
            return m_animations.add(entity);
        }
        static_assert(false, "Unsupported component type");
    }

    // 移除组件
    template<typename T>
    void remove_component(Entity entity) {
        if constexpr (std::is_same_v<T, Transform>) {
            m_transforms.remove(entity);
        } else if constexpr (std::is_same_v<T, Sprite>) {
            m_sprites.remove(entity);
        } else if constexpr (std::is_same_v<T, Actor>) {
            m_actors.remove(entity);
        } else if constexpr (std::is_same_v<T, Collider>) {
            m_colliders.remove(entity);
        } else if constexpr (std::is_same_v<T, Animation>) {
            m_animations.remove(entity);
        }
    }

    // 遍历所有具有特定组件的实体
    template<typename T, typename Func>
    void for_each(Func&& func) {
        if constexpr (std::is_same_v<T, Transform>) {
            for (size_t i = 0; i < m_entities.size(); ++i) {
                if (m_transforms.has(m_entities[i])) {
                    func(m_entities[i], *m_transforms.get(m_entities[i]));
                }
            }
        }
        // 其他组件类型类似...
    }

    // 渲染所有可见精灵
    void render(Renderer& renderer) {
        std::vector<SpriteDrawCmd> cmds;
        for (const auto& entity : m_entities) {
            auto* transform = m_transforms.get(entity);
            auto* sprite = m_sprites.get(entity);
            if (transform && sprite && sprite->visible) {
                SpriteDrawCmd cmd;
                cmd.texture = sprite->texture;
                cmd.source = sprite->source;
                cmd.dest = Rect{
                    transform->position.x,
                    transform->position.y,
                    sprite->source.w * transform->scale.x,
                    sprite->source.h * transform->scale.y
                };
                cmd.color = sprite->color;
                cmd.rotation = transform->rotation;
                cmd.flip_x = sprite->flip_x;
                cmd.flip_y = sprite->flip_y;
                cmd.layer = sprite->layer;
                cmds.push_back(cmd);
            }
        }
        renderer.draw_sprites(cmds);
    }

    // 清空世界
    void clear() {
        m_entities.clear();
        m_transforms.clear();
        m_sprites.clear();
        m_actors.clear();
        m_colliders.clear();
        m_animations.clear();
        m_next_entity_id = 0;
    }

    // 获取实体数量
    size_t entity_count() const { return m_entities.size(); }

    // 查找标记点（用于关卡加载）
    Vec2 find_marker(std::string_view name) const {
        // 简化实现：返回零点
        // 实际应用中需要从关卡数据中查找
        return Vec2::zero();
    }

private:
    std::vector<Entity> m_entities;
    u32 m_next_entity_id = 0;

    ComponentPool<Transform> m_transforms;
    ComponentPool<Sprite> m_sprites;
    ComponentPool<Actor> m_actors;
    ComponentPool<Collider> m_colliders;
    ComponentPool<Animation> m_animations;
};

} // namespace pixel
