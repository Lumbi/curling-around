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
        void chargeShot();
        void shootStone();
        void moveCameraBehindStone();

    private:
        State state;
        Scene *scene;
        CurlingStone *curlingStone;
        Vector3f fieldCenter = { 0, 0, 0 };

        bool chargingShot = false;
        float chargeTime = 0.0f;
        float shotPower = 0.0f;
        const float minShotSpeed = 10.0f;
        const float maxShotSpeed = 50.0f;
};

#endif
