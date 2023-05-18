#ifndef COLLIDER_H
#define COLLIDER_H

/// @brief A sphere-shaped collider.
struct SphereCollider {
    /// @brief The radius of the sphere.
    float radius;
};

/// @brief A collider for a physics body.
struct Collider {
    /// @brief The identifier of the collider kind.
    enum class Kind {
        sphere
    };

    /// @brief The kind of collider.
    Kind kind;

    union {
        /// @brief Available when kind is Collider::Kind::sphere.
        SphereCollider sphere;
    };
};

#endif
