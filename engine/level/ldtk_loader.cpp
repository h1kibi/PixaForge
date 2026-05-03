#include "level/ldtk_loader.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

namespace pf {

bool LdtkLoader::load_project(const std::string& path, LevelData& out_level) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open LDtk file: " << path << "\n";
        return false;
    }

    nlohmann::json root;

    try {
        file >> root;
    } catch (const std::exception& e) {
        std::cout << "Failed to parse LDtk JSON: " << e.what() << "\n";
        return false;
    }

    if (!root.contains("levels") || !root["levels"].is_array() || root["levels"].empty()) {
        std::cout << "LDtk file has no levels.\n";
        return false;
    }

    const auto& level = root["levels"][0];

    out_level.pixel_width = level.value("pxWid", 0);
    out_level.pixel_height = level.value("pxHei", 0);

    if (!level.contains("layerInstances") || !level["layerInstances"].is_array()) {
        std::cout << "Level has no layer instances.\n";
        return false;
    }

    const auto& layers = level["layerInstances"];

    for (const auto& layer : layers) {
        const std::string identifier = layer.value("__identifier", "");

        // Parse Collision IntGrid
        if (identifier == "Collision") {
            const int grid_size = layer.value("__gridSize", 16);
            const int cell_width = layer.value("__cWid", 0);
            const int cell_height = layer.value("__cHei", 0);

            out_level.collision.width = cell_width;
            out_level.collision.height = cell_height;
            out_level.collision.tile_size = grid_size;
            out_level.collision.solid.assign(cell_width * cell_height, 0);

            if (layer.contains("intGridCsv")) {
                const auto& csv = layer["intGridCsv"];

                for (int i = 0; i < csv.size() && i < out_level.collision.solid.size(); ++i) {
                    out_level.collision.solid[i] = csv[i].get<int>() != 0 ? 1 : 0;
                }
            }
        }

        // Parse Entities
        if (identifier == "Entities") {
            const auto& entities = layer["entityInstances"];

            for (const auto& entity : entities) {
                const std::string entity_id = entity.value("__identifier", "");

                if (entity_id == "PlayerSpawn") {
                    const auto& px = entity["px"];

                    out_level.player_spawn.x = px[0].get<float>();
                    out_level.player_spawn.y = px[1].get<float>();
                    out_level.has_player_spawn = true;
                }
            }
        }
    }

    std::printf("LDtk loaded: %dx%d, collision: %dx%d, spawn: %s\n",
        out_level.pixel_width, out_level.pixel_height,
        out_level.collision.width, out_level.collision.height,
        out_level.has_player_spawn ? "yes" : "no");

    return true;
}

}
