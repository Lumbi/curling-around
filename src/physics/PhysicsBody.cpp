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
