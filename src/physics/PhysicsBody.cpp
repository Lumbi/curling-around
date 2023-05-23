#include "PhysicsBody.hpp"

static PhysicsBody::ID idSequence = 0;

PhysicsBody::PhysicsBody()
    : id(idSequence++)
{}

PhysicsBody PhysicsBody::makeSphere(float mass, float radius)
{
    PhysicsBody body;
    body.mass = mass;
    body.collider = { Collider::Kind::sphere, { radius } };
    return body;
}
