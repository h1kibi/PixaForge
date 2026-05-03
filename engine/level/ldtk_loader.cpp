#include "level/ldtk_loader.h"

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

namespace pf {

bool LdtkLoader::load_project(const std::string& path, LevelData& out_level) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::printf("Failed to open LDtk file: %s\n", path.c_str());
        return false;
    }

    nlohmann::json root;

    try {
        file >> root;
    } catch (const std::exception& e) {
        std::printf("Failed to parse LDtk JSON: %s\n", e.what());
        return false;
    }

    if (!root.contains("levels") || !root["levels"].is_array() || root["levels"].empty()) {
        std::printf("LDtk file has no levels.\n");
        return false;
    }

    const auto& level = root["levels"][0];

    out_level.pixel_width = level.value("pxWid", 0);
    out_level.pixel_height = level.value("pxHei", 0);

    // Reset data
    out_level.checkpoints.clear();
    out_level.hazards.clear();
    out_level.goals.clear();
    out_level.has_player_spawn = false;

    if (!level.contains("layerInstances") || !level["layerInstances"].is_array()) {
        std::printf("Level has no layer instances.\n");
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

            std::printf("  Collision: %dx%d (tile %d)\n", cell_width, cell_height, grid_size);
        }

        // Parse Entities
        if (identifier == "Entities") {
            const auto& entities = layer["entityInstances"];

            for (const auto& entity : entities) {
                const std::string entity_id = entity.value("__identifier", "");
                const auto& px = entity["px"];

                if (entity_id == "PlayerSpawn") {
                    out_level.player_spawn.x = px[0].get<float>();
                    out_level.player_spawn.y = px[1].get<float>();
                    out_level.has_player_spawn = true;
                    std::printf("  PlayerSpawn: (%.0f, %.0f)\n",
                        out_level.player_spawn.x, out_level.player_spawn.y);
                }
                else if (entity_id == "Checkpoint") {
                    LevelCheckpoint cp;
                    cp.x = px[0].get<float>();
                    cp.y = px[1].get<float>();
                    out_level.checkpoints.push_back(cp);
                    std::printf("  Checkpoint: (%.0f, %.0f)\n", cp.x, cp.y);
                }
                else if (entity_id == "Hazard") {
                    LevelHazard hazard;
                    hazard.bounds.x = px[0].get<float>();
                    hazard.bounds.y = px[1].get<float>();
                    hazard.bounds.w = entity.value("width", 16.0f);
                    hazard.bounds.h = entity.value("height", 16.0f);
                    out_level.hazards.push_back(hazard);
                    std::printf("  Hazard: (%.0f, %.0f) %.0fx%.0f\n",
                        hazard.bounds.x, hazard.bounds.y, hazard.bounds.w, hazard.bounds.h);
                }
                else if (entity_id == "Goal") {
                    LevelGoal goal;
                    goal.bounds.x = px[0].get<float>();
                    goal.bounds.y = px[1].get<float>();
                    goal.bounds.w = entity.value("width", 16.0f);
                    goal.bounds.h = entity.value("height", 16.0f);
                    out_level.goals.push_back(goal);
                    std::printf("  Goal: (%.0f, %.0f) %.0fx%.0f\n",
                        goal.bounds.x, goal.bounds.y, goal.bounds.w, goal.bounds.h);
                }
            }
        }
    }

    std::printf("LDtk loaded: %dx%d\n", out_level.pixel_width, out_level.pixel_height);
    return true;
}

}
