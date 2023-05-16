#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "math/Vector.hpp"

class Scene;
class CurlingStone;

class PlayerController {
    public:
        enum class State {
            aiming,
            sliding,
            waiting
        };

    public:
        PlayerController(Scene *);

        void update();

    private:
        void spawnStone();
        void throwStone();
        void moveCameraBehindStone();

    private:
        State state;
        Scene *scene;
        CurlingStone *curlingStone;
        Vector3f fieldCenter = { 0, 0, 0 };
};

#endif
