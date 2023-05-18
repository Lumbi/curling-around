#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.hpp"
#include "Matrix.hpp"

/// @brief A class to encapsulate a position and rotation.
class Transform
{
    public:
        /// @brief Initialize a transform at origin with no rotation.
        Transform();

        /// @brief Get the position of the transform.
        Vector3f getPosition() const;

        /// @brief Set the position of the transform.
        void setPosition(const Vector3f &);

        /// @brief Translate the transform by the specified vector.
        void translateBy(const Vector3f &);

        /// @brief Get the rotation of the transform.
        Vector3f getRotation() const;

        /// @brief Set the rotation of the transform.
        void setRotation(const Vector3f &);

        /// @brief Rotate the transform by the specified vector.
        ///        Each component rotates the transform by the amount in radians around the corresponding axis.
        void rotateBy(const Vector3f &);

        // TODO: Support scale

        /// @brief Get the transformation matrix from the position and rotation.
        Matrix4f getMatrix() const;

    private:
        Vector3f position;
        Vector3f rotation;
};

#endif