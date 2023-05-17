#include "Physics.hpp"

#include "physics/PhysicsBody.hpp"
#include "physics/Collisions.hpp"

#include <algorithm>

Physics & Physics::shared() {
    static Physics instance;
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
        if (!firstBody) continue;
        for (auto&& secondBody : physicsBodies) {
            if (!secondBody) continue;
            if (firstBody == secondBody) continue;
            switch (firstBody->collider.kind) {
            case Collider::Kind::sphere:
                switch (secondBody->collider.kind) {
                case Collider::Kind::sphere:
                    handleSphereToSphereCollision(*firstBody, *secondBody);
                    break;
                }
                break;
            }
        }
    }
}
