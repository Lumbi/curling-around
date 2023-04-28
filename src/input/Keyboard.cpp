#include "Keyboard.hpp"

void Keyboard::handle(const SDL_Event &event)
{
    switch (event.type) {
        case SDL_KEYDOWN: {
            const SDL_Keycode keyCode = event.key.keysym.sym;
            state[keyCode].isPressed = true;
            break;
        }
        case SDL_KEYUP: {
            const SDL_Keycode keyCode = event.key.keysym.sym;
            state[keyCode].isPressed = false;
            break;
        }
    }
}

bool Keyboard::isPressed(SDL_Keycode keyCode)
{
    return state[keyCode].isPressed;
}
