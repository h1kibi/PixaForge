#include "input/sdl_input.h"

namespace pf {

namespace {

bool is_left_key(SDL_Scancode scancode) {
    return scancode == SDL_SCANCODE_A ||
           scancode == SDL_SCANCODE_LEFT;
}

bool is_right_key(SDL_Scancode scancode) {
    return scancode == SDL_SCANCODE_D ||
           scancode == SDL_SCANCODE_RIGHT;
}

bool is_jump_key(SDL_Scancode scancode) {
    return scancode == SDL_SCANCODE_SPACE ||
           scancode == SDL_SCANCODE_W ||
           scancode == SDL_SCANCODE_UP;
}

bool is_quit_key(SDL_Scancode scancode) {
    return scancode == SDL_SCANCODE_ESCAPE;
}

}

void handle_sdl_input_event(Input& input, const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.repeat) {
            return;
        }

        const SDL_Scancode scancode = event.key.scancode;

        if (is_left_key(scancode)) {
            input.press_action(Action::MoveLeft);
        } else if (is_right_key(scancode)) {
            input.press_action(Action::MoveRight);
        } else if (is_jump_key(scancode)) {
            input.press_action(Action::Jump);
        } else if (is_quit_key(scancode)) {
            input.press_action(Action::Quit);
            input.press_action(Action::Pause);
        }
    }

    if (event.type == SDL_EVENT_KEY_UP) {
        const SDL_Scancode scancode = event.key.scancode;

        if (is_left_key(scancode)) {
            input.release_action(Action::MoveLeft);
        } else if (is_right_key(scancode)) {
            input.release_action(Action::MoveRight);
        } else if (is_jump_key(scancode)) {
            input.release_action(Action::Jump);
        } else if (is_quit_key(scancode)) {
            input.release_action(Action::Quit);
            input.release_action(Action::Pause);
        }
    }
}

}
