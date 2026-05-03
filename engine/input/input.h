#pragma once

#include <array>

#include "input/action.h"

namespace pf {

class Input {
public:
    void begin_frame();

    void set_action(Action action, bool down);

    void press_action(Action action);
    void release_action(Action action);

    bool down(Action action) const;
    bool pressed(Action action) const;
    bool released(Action action) const;

    float axis_move_x() const;

private:
    std::array<bool, action_count()> current_{};
    std::array<bool, action_count()> previous_{};

    // -1 = left, 0 = none, 1 = right
    int horizontal_priority_ = 0;
};

}
