#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.hpp"

class Input {
    public:
        static Input& shared();

        void update();

    public:
        Keyboard keyboard;
        bool quit = false;

    private:
        Input();
};

#endif
