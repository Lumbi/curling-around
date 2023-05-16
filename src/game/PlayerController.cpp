#include "PlayerController.hpp"

#include "Scene.hpp"
#include "rendering/Camera.hpp"
#include "math/Vector.hpp"
#include "game/actors/CurlingStone.hpp"
#include "physics/PhysicsBody.hpp"
#include "input/Input.hpp"

#include <memory>
#include <math.h>

static const SDL_KeyCode SHOOT_KEY = SDLK_SPACE;

PlayerController::PlayerController(Scene *scene)
    : scene(scene), state(State::aiming), curlingStone(nullptr)
{}

void PlayerController::update()
{
    switch (state) {
        case State::aiming: {
            if (!curlingStone) spawnStone();

            if (Input::shared().keyboard.isPressed(SHOOT_KEY)) { // Holding down on shoot key
                chargingShot = true;
                chargeShot();

            } else if (chargingShot) { // Released shoot key and was charging
                if (shotPowerDelta > 0.0f) {
                    shootStone();
                    state = State::sliding;
                } else { // Cancel if swinging backwards
                    curlingStone->getBody()->position = spawnPosition;
                    state = State::aiming;
                }
                chargingShot = false;
                chargeTime = 0.f;
                shotPowerDelta = 0.f;
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

    updateCamera();
}

void PlayerController::spawnStone()
{
    auto newCurlingStone = std::make_unique<CurlingStone>();
    PhysicsBody *body = newCurlingStone->getBody();
    if (body) {
        body->position = spawnPosition;
    }
    curlingStone = newCurlingStone.get();
    scene->getRoot()->addChild(std::move(newCurlingStone));
    moveCameraBehindStone();
}

void PlayerController::chargeShot()
{
    if (!curlingStone) { return; }
    float previousShotPower = shotPower;
    shotPower = (sinf(chargeTime) * sinf(chargeTime));
    chargeTime += chargeSpeed;
    shotPowerDelta = shotPower - previousShotPower;

    PhysicsBody *body = curlingStone->getBody();
    Vector3f direction = normalize(fieldCenter - body->position);
    Vector3f swingLocation = spawnPosition + (direction * shotPower * swingDistance);
    body->position = swingLocation;
}

void PlayerController::shootStone()
{
    if (!curlingStone) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    Vector3f direction = fieldCenter - body->position;
    direction.y = 0.f;
    direction = normalize(direction);

    float throwSpeed = minShotSpeed + shotPower * maxShotSpeed;
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
    float distanceBehind = 700.f;
    float distanceAbove = 500.f;
    Vector3f targetPosition = body->position;
    Vector3f displacementBehind = fieldCenterToStone * distanceBehind;
    Vector3f displacementAbove = { 0.f, distanceAbove, 0.f };
    targetPosition += (displacementBehind + displacementAbove);

    cameraTargetPosition = targetPosition;
}

void PlayerController::updateCamera()
{
    if (!curlingStone) { return; }
    Camera *camera = scene->getCamera();
    if (!camera) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    Vector3f fieldCenterToStone = normalize(body->position - fieldCenter);

    camera->transform.setPosition(
        lerp(camera->transform.getPosition(), cameraTargetPosition, 0.1f)
    );

    // Look at
    // TODO: Use LookAt matrix
    float rotationY = atan2f(fieldCenterToStone.z, fieldCenterToStone.x) - M_PI_2;
    float rotationX = 20.0f * (M_PI / 360.0f);
    camera->transform.setRotation({ rotationX, rotationY, 0.f });
}
