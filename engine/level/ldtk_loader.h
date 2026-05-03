#pragma once

#include <string>

#include "level/level_data.h"

namespace pf {

class LdtkLoader {
public:
    bool load_project(const std::string& path, LevelData& out_level);
};

}
