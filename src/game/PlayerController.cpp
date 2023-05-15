#include "PlayerController.hpp"

#include "Scene.hpp"
#include "math/Vector.hpp"
#include "game/actors/CurlingStone.hpp"
#include "physics/PhysicsBody.hpp"
#include "input/Input.hpp"

#include <memory>

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
            if (curlingStone->getBody()->isResting()) {
                printf("STATE: State::aiming\n");
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
}

void PlayerController::throwStone()
{
    if (!curlingStone) { return; }
    PhysicsBody *body = curlingStone->getBody();
    if (!body) { return; }

    Vector3f center = { 0, 0, 0 };
    Vector3f direction = center - body->position;
    direction.y = 0;
    direction = normalize(direction);

    float throwSpeed = 50.0f;
    body->velocity = throwSpeed * direction;
}
