#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "math/Vector.hpp"
#include "physics/Collider.hpp"

/// @brief Represents a body that interacts with other bodies inside a physics simulation.
class PhysicsBody {
    public:
        /// @brief The type of body which defines how the body reacts inside the physics simulation.
        enum Type {
            /// @brief The body moves in response to forces and collisions.
            dynamic,
            /// @brief The body is immovable and acts as an object with infinite mass.
            fixed
        };

        using ID = int;
        /// @brief The unique identifier of this body.
        const ID id;

        using Tag = int;
        /// @brief An arbitrary identifier that can be used to provide additional properties to the body.
        Tag tag = 0;

        /// @brief The type of body.
        Type type = Type::dynamic;

        /// @brief The mass of the body in arbitrary units.
        float mass = 0.f;

        /// @brief How much the body bounces back in a collision.
        ///        Values between 0 and 1 reduce the bounciness. Values above 1 increase the bounciness.
        float bounciness = 1.f;

        /// @brief The world space position of the body.
        Vector3f position = Vector3f::zero;

        /// @brief The world space velocity of the body.
        Vector3f velocity = Vector3f::zero;

        /// @brief The body's collider.
        Collider collider;

    public:
        /// @brief A factory method to create a physics body with sphere collider.
        /// @param mass The mass of the physics body.
        /// @param radius The radius of the sphere collider.
        /// @return A new physics body centered at the origin.
        static PhysicsBody makeSphere(float mass, float radius);

    private:
        PhysicsBody();
};

#endif
