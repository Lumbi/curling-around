#include "Input.hpp"

#include <SDL.h>

Input &Input::shared() {
    static Input instance;
    return instance;
}

void Input::update() {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        keyboard.handle(event);

        switch (event.type) {
                case SDL_QUIT: {
                quit = true;
                break;
            }
        }
    }
}

Input::Input()
{}
