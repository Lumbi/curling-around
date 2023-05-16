#include "PlayerController.hpp"

#include "Scene.hpp"
#include "rendering/Camera.hpp"
#include "math/Vector.hpp"
#include "game/actors/CurlingStone.hpp"
#include "physics/PhysicsBody.hpp"
#include "input/Input.hpp"

#include <memory>
#include <math.h>

PlayerController::PlayerController(Scene *scene)
    : scene(scene), state(State::aiming), curlingStone(nullptr)
{}

void PlayerController::update()
{
    switch (state) {
        case State::aiming: {
            if (!curlingStone) spawnStone();
            if (Input::shared().keyboard.isPressed(SDLK_SPACE)) {
                throwStone();
                state = State::sliding;
            }
            break;
        }

        case State::sliding: {
            if (!curlingStone) state = State::aiming; // TODO: Replace with waiting
            moveCameraBehindStone();
            if (curlingStone->getBody()->isResting()) {
                curlingStone = nullptr;
                state = State::aiming; // TODO: Replace with waiting
            }
            break;
        }

        case State::waiting: {
            break;
        }
    }
}

void PlayerController::spawnStone()
{
    Vector3f spawnLocation = { 0, 0, 1700 };
    auto newCurlingStone = std::make_unique<CurlingStone>();
    PhysicsBody *body = newCurlingStone->getBody();
    if (body) {
        body->position = spawnLocation;
    }
    curlingStone = newCurlingStone.get();
    scene->getRoot()->addChild(std::move(newCurlingStone));
    moveCameraBehindStone();
}

void PlayerController::throwStone()
{
    if (!curlingStone) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    Vector3f direction = fieldCenter - body->position;
    direction.y = 0;
    direction = normalize(direction);

    float throwSpeed = 50.0f;
    body->velocity = throwSpeed * direction;
}

void PlayerController::moveCameraBehindStone()
{
    if (!curlingStone) { return; }
    Camera *camera = scene->getCamera();
    if (!camera) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    Vector3f fieldCenterToStone = normalize(body->position - fieldCenter);

    // Follow behind
    float distanceBehind = 700.0f;
    float distanceAbove = 500.0f;
    Vector3f targetPosition = body->position;
    Vector3f displacementBehind = fieldCenterToStone * distanceBehind;
    Vector3f displacementAbove = { 0, distanceAbove, 0 };
    targetPosition += (displacementBehind + displacementAbove);
    camera->transform.setPosition(targetPosition);

    // Look at
    // TODO: Use LookAt matrix
    float rotationY = atan2f(fieldCenterToStone.z, fieldCenterToStone.x) - M_PI_2;
    float rotationX = 20.0f * (M_PI / 360.0f);
    camera->transform.setRotation({ rotationX, rotationY, 0 });
}
