#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>
#include <unordered_map>

struct KeyState
{
    bool isPressed;

    KeyState(): isPressed(false) {}
};

class Keyboard
{
    public:
        void handle(const SDL_Event &);
        bool isPressed(SDL_Keycode);

    private:
        std::unordered_map<SDL_Keycode, KeyState> state;
};

#endif