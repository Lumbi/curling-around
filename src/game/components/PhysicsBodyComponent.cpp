#include "PhysicsBodyComponent.hpp"

#include "game/Actor.hpp"
#include "physics/Physics.hpp"

PhysicsBodyComponent::PhysicsBodyComponent(PhysicsBody physicsBody)
    : physicsBody(physicsBody)
{
    Physics::shared().addPhysicsBody(&this->physicsBody);
}

PhysicsBodyComponent::~PhysicsBodyComponent()
{
    Physics::shared().removePhysicsBody(&physicsBody);
}

void PhysicsBodyComponent::update()
{
    Actor *actor = getActor();
    if (actor) {
        actor->getTransform().setPosition(physicsBody.position);
    }

    // Very simple linear friction
    physicsBody.velocity *= (1.0f - friction);
}

void PhysicsBodyComponent::draw(Renderer &)
{}

PhysicsBody & PhysicsBodyComponent::getBody()
{
    return physicsBody;
}

void PhysicsBodyComponent::setFriction(float newFriction)
{
    this->friction = newFriction;
}
