#include "input/input.h"

namespace pf {

void Input::begin_frame() {
    previous_ = current_;
}

void Input::set_action(Action action, bool down) {
    if (down) {
        press_action(action);
    } else {
        release_action(action);
    }
}

void Input::press_action(Action action) {
    current_[static_cast<std::uint32_t>(action)] = true;

    if (action == Action::MoveLeft) {
        horizontal_priority_ = -1;
    } else if (action == Action::MoveRight) {
        horizontal_priority_ = 1;
    }
}

void Input::release_action(Action action) {
    current_[static_cast<std::uint32_t>(action)] = false;

    if (action == Action::MoveLeft && horizontal_priority_ == -1) {
        horizontal_priority_ = down(Action::MoveRight) ? 1 : 0;
    } else if (action == Action::MoveRight && horizontal_priority_ == 1) {
        horizontal_priority_ = down(Action::MoveLeft) ? -1 : 0;
    }
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
    const bool left = down(Action::MoveLeft);
    const bool right = down(Action::MoveRight);

    if (left && right) {
        return static_cast<float>(horizontal_priority_);
    }

    if (left) {
        return -1.0f;
    }

    if (right) {
        return 1.0f;
    }

    return 0.0f;
}

}
