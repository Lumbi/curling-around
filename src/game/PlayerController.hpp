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
        void updateCamera();

    private:
        State state;
        Scene *scene;
        CurlingStone *curlingStone;

        // Positions
        Vector3f fieldCenter = { 0, 0, 0 };
        Vector3f spawnPosition = { 0, 0, 1700 };

        // Camera
        Vector3f cameraTargetPosition = Vector3f::zero;

        // Stone shooting
        bool chargingShot = false;
        float chargeTime = 0.0f;
        float chargeSpeed = 0.1f;
        float swingDistance = 150.0f;
        float shotPower = 0.0f;
        float shotPowerDelta = 0.0f;
        const float minShotSpeed = 10.0f;
        const float maxShotSpeed = 50.0f;
};

#endif
