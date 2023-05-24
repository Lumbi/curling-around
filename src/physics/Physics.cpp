#include "Physics.hpp"

#include "physics/Collisions.hpp"
#include "Time.hpp"

#include <algorithm>

Physics & Physics::shared() {
    static Physics instance;
    return instance;
}

Physics::Physics()
{}

void Physics::addPhysicsBody(PhysicsBody *physicsBody)
{
    if (!physicsBody) { return; }
    physicsBodies.push_back(physicsBody);
}

void Physics::removePhysicsBody(PhysicsBody *physicsBody)
{
    if (!physicsBody) { return; }
    std::erase(physicsBodies, physicsBody);
}

void Physics::update()
{
    // Clear collision contacts
    contacts.clear();

    // Update simulation
    for (auto&& body : physicsBodies) {
        if (body) {
            if (body->type == PhysicsBody::Type::dynamic) {
                body->position += (body->velocity * Time::shared().deltaTime);
            }
        }
    }

    // Handle collisions
    for (auto&& firstBody : physicsBodies) {
        if (!firstBody) continue;
        for (auto&& secondBody : physicsBodies) {
            if (!secondBody) continue;
            if (firstBody == secondBody) continue;
            bool didCollide = false;
            switch (firstBody->collider.kind) {
            case Collider::Kind::sphere:
                switch (secondBody->collider.kind) {
                case Collider::Kind::sphere:
                    didCollide |= handleSphereToSphereCollision(*firstBody, *secondBody);
                    break;
                }
                break;
            }
            if (didCollide) {
                contacts[firstBody->id].push_back(secondBody);
                contacts[secondBody->id].push_back(firstBody);
            }
        }
    }
}

const std::vector<PhysicsBody *> &Physics::getContacts(PhysicsBody::ID id)
{
    return contacts[id];
}
