#include "PhysicsBody.hpp"

PhysicsBody PhysicsBody::makeSphere(float mass, float radius)
{
    return PhysicsBody {
        Type::dynamic,
        mass,
        1.0f,
        Vector3f::zero,
        Vector3f::zero,
        { Collider::Kind::sphere, { radius } }
    };
}
