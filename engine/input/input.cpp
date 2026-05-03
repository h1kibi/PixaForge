#include "input/input.h"

namespace pf {

void Input::begin_frame() {
    previous_ = current_;
}

void Input::set_action(Action action, bool down) {
    current_[static_cast<std::uint32_t>(action)] = down;
}

bool Input::down(Action action) const {
    return current_[static_cast<std::uint32_t>(action)];
}

bool Input::pressed(Action action) const {
    const auto index = static_cast<std::uint32_t>(action);
    return current_[index] && !previous_[index];
}

bool Input::released(Action action) const {
    const auto index = static_cast<std::uint32_t>(action);
    return !current_[index] && previous_[index];
}

float Input::axis_move_x() const {
    float value = 0.0f;

    if (down(Action::MoveLeft)) {
        value -= 1.0f;
    }

    if (down(Action::MoveRight)) {
        value += 1.0f;
    }

    return value;
}

}
