#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "math/Vector.hpp"
#include "physics/Collider.hpp"

struct PhysicsBody {
    enum class Kind {
        sphere
    };

    Kind kind;
    float mass;
    Vector3f position;
    Vector3f velocity;
    Vector3f acceleration;
    Collider collider;

    static PhysicsBody makeSphere(float mass, float radius);
};

#endif
