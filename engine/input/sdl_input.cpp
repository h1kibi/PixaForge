#include "input/sdl_input.h"

#include <SDL3/SDL.h>

namespace pf {

void update_input_from_sdl_keyboard(Input& input) {
    const bool* keys = SDL_GetKeyboardState(nullptr);

    const bool move_left =
        keys[SDL_SCANCODE_A] ||
        keys[SDL_SCANCODE_LEFT];

    const bool move_right =
        keys[SDL_SCANCODE_D] ||
        keys[SDL_SCANCODE_RIGHT];

    const bool jump =
        keys[SDL_SCANCODE_SPACE] ||
        keys[SDL_SCANCODE_W] ||
        keys[SDL_SCANCODE_UP];

    const bool pause =
        keys[SDL_SCANCODE_ESCAPE];

    input.set_action(Action::MoveLeft, move_left);
    input.set_action(Action::MoveRight, move_right);
    input.set_action(Action::Jump, jump);
    input.set_action(Action::Pause, pause);
    input.set_action(Action::Quit, pause);
}

}
