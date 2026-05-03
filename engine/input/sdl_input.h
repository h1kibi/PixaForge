#pragma once

#include <SDL3/SDL.h>

#include "input/input.h"

namespace pf {

void handle_sdl_input_event(Input& input, const SDL_Event& event);

}
