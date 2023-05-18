#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "math/Vector.hpp"
#include "physics/Collider.hpp"

/// @brief Represents a body that interacts with other bodies inside a physics simulation.
struct PhysicsBody {

    /// @brief The type of body which defines how the body reacts inside the physics simulation.
    enum Type {
        /// @brief The body moves in response to forces and collisions.
        dynamic,
        /// @brief The body is immovable and acts as an object with infinite mass.
        fixed
    };

    /// @brief The type of body.
    Type type;

    /// @brief The mass of the body in arbitrary units.
    float mass;

    /// @brief The world space position of the body.
    Vector3f position;

    /// @brief The world space velocity of the body.
    Vector3f velocity;

    /// @brief The body's collider.
    Collider collider;

    /// @brief A convenience factory method to create a physics body with sphere collider.
    /// @param mass The mass of the physics body.
    /// @param radius The radius of the sphere collider.
    /// @return A new physics body centered at the origin.
    static PhysicsBody makeSphere(float mass, float radius);
};

#endif
