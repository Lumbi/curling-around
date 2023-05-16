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
static const SDL_KeyCode AIM_LEFT_KEY = SDLK_LEFT;
static const SDL_KeyCode AIM_RIGHT_KEY = SDLK_RIGHT;

PlayerController::PlayerController(Scene *scene)
    : scene(scene), state(State::aiming), curlingStone(nullptr)
{}

void PlayerController::update()
{
    switch (state) {
        case State::aiming: {
            if (!curlingStone) spawnStone();
            aimShot();
            if (Input::shared().keyboard.isPressed(SHOOT_KEY)) {
                state = State::charging;
            }
            break;
        }

        case State::charging: {
            chargeShot();
            if (!Input::shared().keyboard.isPressed(SHOOT_KEY)) { // Released shoot key and was charging
                if (shotPowerDelta > 0.0f) {
                    shootStone();
                    state = State::sliding;
                } else { // Cancel if swinging backwards
                    curlingStone->getBody()->position = spawnPosition;
                    state = State::aiming;
                }
                chargeTime = 0.f;
                shotPowerDelta = 0.f;
            }
            break;
        }

        case State::sliding: {
            if (!curlingStone) state = State::waiting;
            moveCameraBehindStone();
            if (curlingStone->getBody()->velocity.length() < 0.5f) {
                curlingStone = nullptr;
                state = State::waiting;
            }
            break;
        }

        case State::waiting: {
            waitTime += 1.f / 60.f; // TODO: Use delta time
            if (waitTime >= waitDelay) {
                endTurn();
                state = State::aiming;
                waitTime = 0.f;
            }
            break;
        }
    }

    updateCamera();
}

void PlayerController::spawnStone()
{
    auto newCurlingStone = std::make_unique<CurlingStone>(currentPlayerID);
    PhysicsBody *body = newCurlingStone->getBody();
    if (body) { body->position = spawnPosition; }
    curlingStone = newCurlingStone.get();
    scene->getRoot()->addChild(std::move(newCurlingStone));
    moveCameraBehindStone();
}

void PlayerController::aimShot()
{
    if (!curlingStone) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    if (Input::shared().keyboard.isPressed(AIM_LEFT_KEY)) {
        aimAngle += aimSpeed;
    }

    if (Input::shared().keyboard.isPressed(AIM_RIGHT_KEY)) {
        aimAngle -= aimSpeed;
    }

    spawnPosition = { cosf(aimAngle) * spawnDistance, 0.f, sinf(aimAngle) * spawnDistance };
    body->position = spawnPosition;

    // Align the stone with the center
    curlingStone->getTransform().setRotation({ 0.f, aimAngle, 0.f });

    moveCameraBehindStone(true); // immediate
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

void PlayerController::endTurn()
{
    if (currentPlayerID == 0) {
        currentPlayerID = 1;
    } else {
        currentPlayerID = 0;
    }
}

void PlayerController::moveCameraBehindStone(bool immediate)
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

    // Avoid chasing the curling stone if it's too far
    if (distance(spawnPosition, targetPosition) < spawnDistance) {
        cameraTargetPosition = targetPosition;
        if (immediate) {
            camera->transform.setPosition(cameraTargetPosition);
        }
    }
}

void PlayerController::updateCamera()
{
    if (!curlingStone) { return; }
    Camera *camera = scene->getCamera();
    if (!camera) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    // Animate position
    camera->transform.setPosition(
        lerp(camera->transform.getPosition(), cameraTargetPosition, 0.1f)
    );

    // Look at curling stone
    // TODO: Use LookAt matrix
    Vector3f viewDirection = normalize(cameraTargetPosition - fieldCenter);
    float yaw = atan2f(viewDirection.z, viewDirection.x) - M_PI_2;
    float pitch = 20.0f * (M_PI / 360.0f);
    camera->transform.setRotation({ pitch, yaw, 0.f });
}
