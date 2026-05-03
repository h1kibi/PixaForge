#pragma once

#include <cstdint>

namespace pf {

struct TextureHandle {
    std::uint32_t id = 0;

    bool valid() const {
        return id != 0;
    }
};

}
