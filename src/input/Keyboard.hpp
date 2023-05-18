#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>
#include <unordered_map>

/// @brief The state of a key.
struct KeyState
{
    /// @brief Whether the key is currently pressed.
    bool isPressed;

    /// @brief Initialize the key state.
    KeyState(): isPressed(false) {}
};

/// @brief A class to manage keyboard related input states.
class Keyboard
{
    public:
        /// @brief Handle an input event and update the keyboard state.
        void handle(const SDL_Event &);

        /// @brief Get the current pressed state of the specified key.
        bool isPressed(SDL_Keycode);

    private:
        std::unordered_map<SDL_Keycode, KeyState> state;
};

#endif