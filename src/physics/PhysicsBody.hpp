#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "math/Vector.hpp"
#include "physics/Collider.hpp"

struct PhysicsBody {
    enum Type {
        dynamic,
        fixed
    };

    Type type;
    float mass;
    Vector3f position;
    Vector3f velocity;
    Collider collider;

    static PhysicsBody makeSphere(float mass, float radius);
};

#endif
