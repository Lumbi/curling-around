#include "Physics.hpp"

#include "physics/PhysicsBody.hpp"

#include <algorithm>

Physics * Physics::instance = nullptr;

Physics * Physics::shared() {
    if (instance == nullptr) {
        instance = new Physics();
    }
    return instance;
}

Physics::Physics()
{}

void Physics::addPhysicsBody(PhysicsBody *physicsBody)
{
    physicsBodies.push_back(physicsBody);
}

void Physics::removePhysicsBody(PhysicsBody *physicsBody)
{
    std::erase(physicsBodies, physicsBody);
}

void Physics::update()
{
    // Update simulation
    for (auto&& body : physicsBodies) {
        if (body) {
            body->velocity += body->acceleration;
            body->position += body->velocity;
        }
    }

    // Handle collisions
    for (auto&& firstBody : physicsBodies) {
        for (auto&& secondBody : physicsBodies) {

        }
    }
}
