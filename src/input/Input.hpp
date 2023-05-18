#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.hpp"

/// @brief A singleton class to manage input state and events.
class Input {
    public:
        /// @brief Get the shared singleton instance.
        static Input& shared();

        /// @brief Update input states.
        void update();

    public:
        /// @brief The input states related to the keyboard.
        Keyboard keyboard;

        /// @brief A flag denoting an input intent to quit.
        bool quit = false;

    private:
        Input();
};

#endif
