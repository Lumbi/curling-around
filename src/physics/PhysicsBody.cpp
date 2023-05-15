#include "PhysicsBody.hpp"

PhysicsBody PhysicsBody::makeSphere(float mass, float radius)
{
    return PhysicsBody {
        Kind::sphere,
        mass,
        Vector3f::zero,
        Vector3f::zero,
        Vector3f::zero,
        SphereCollider { radius }
    };
}

bool PhysicsBody::isResting() const
{
    const float epslion = 0.1f;
    return velocity.length() < epslion; // TODO: Optimize using length squared
}
