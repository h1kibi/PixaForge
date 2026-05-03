#pragma once

#include <array>

#include "input/action.h"

namespace pf {

class Input {
public:
    void begin_frame();

    void set_action(Action action, bool down);

    bool down(Action action) const;
    bool pressed(Action action) const;
    bool released(Action action) const;

    float axis_move_x() const;

private:
    std::array<bool, action_count()> current_{};
    std::array<bool, action_count()> previous_{};
};

}
