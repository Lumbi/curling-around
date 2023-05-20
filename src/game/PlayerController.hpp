#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "math/Vector.hpp"

class Scene;
class Camera;
class CurlingStone;

/// @brief A class to control the player's actions and update the camera accordingly.
class PlayerController {
    public:
        /// @brief The player controller's state.
        enum class State {
            aiming,
            charging,
            sliding,
            waiting
        };

    public:
        /// @brief Initialize the player controller.
        /// @param scene The scene in which to play.
        /// @param camera The camera to control.
        PlayerController(Scene *scene, Camera *camera);

        /// @brief Update the player controller for a single frame.
        void update();

    private:
        /// @brief Create a curling stone at the current spawn location
        void spawnStone();

        /// @brief Handle the inputs for aiming the curling stone.
        void aimShot();

        /// @brief Handle the inputs for swinging the curling stone.
        void chargeShot();

        /// @brief Shoot the culing stone by setting its velocity.
        void shootStone();

        /// @brief End turn and switch the current player.
        void endTurn();

        /// @brief Place the camera's target position behind the curling stone, facing the curling stone.
        /// @param immediate If true, immediately jump to the position without animating.
        void moveCameraBehindStone(bool immediate = false);

        /// @brief Place the camera's target position up high, facing the field center.
        void moveCameraBirdseye();

        /// @brief Update the camera to move toward the target location and rotation.
        void updateCamera();

    private:
        Scene *scene;
        Camera *camera;
        State state = State::aiming;
        CurlingStone *curlingStone = nullptr;

        // Positions
        Vector3f fieldCenter = Vector3f::zero;
        const float spawnDistance = 1700.f;
        Vector3f spawnPosition;

        // Camera
        Vector3f cameraTargetPosition = Vector3f::zero;
        Vector3f cameraTargetRotation = Vector3f::zero;
        const float cameraSpeed = 5.f;

        // Game state
        int currentPlayerID = 0;

        // Aiming
        float aimAngle = 0.f;
        float aimSpeed = 1.8f; // in radians per seconds

        // Charging
        float chargeTime = 0.f;
        float chargeSpeed = 3.f;
        float swingDistance = 200.f;
        float shotPower = 0.f;
        float shotPowerDelta = 0.f;
        const float minShotSpeed = 600.f;
        const float maxShotSpeed = 4000.f;

        // Waiting
        const float waitDelay = 1.f;
        float waitTime = 0.f;
};

#endif
