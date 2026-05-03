#pragma once

#include <cstdint>

namespace pf {

enum class Action : std::uint8_t {
    MoveLeft,
    MoveRight,
    Jump,
    Attack,
    Dash,
    Pause,
    Quit,
    Reload,

    Count
};

constexpr std::uint32_t action_count() {
    return static_cast<std::uint32_t>(Action::Count);
}

}
