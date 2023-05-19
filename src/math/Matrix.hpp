#ifndef MATRIX_H
#define MATRIX_H

#include "math/Index.hpp"
#include "math/Vector.hpp"

/// @brief A 4x4 matrix of floats.
struct Matrix4f
{
    /// @brief The matrix data arranged in consecutive rows.
    float data[16];

    /// @brief Get the identity matrix.
    static Matrix4f identity();

    /// @brief Create a translation matrix.
    /// @param tx X-axis component of the translation.
    /// @param ty Y-axis component of the translation.
    /// @param tz Z-axis component of the translation.
    static Matrix4f translation(float tx, float ty, float tz);

    /// @brief Create a translation matrix around the X-axis.
    /// @param radians The rotation amount in radians.
    static Matrix4f rotation_x(float radians);

    /// @brief Create a translation matrix around the Y-axis.
    /// @param radians The rotation amount in radians.
    static Matrix4f rotation_y(float radians);

    /// @brief Create a translation matrix around the Z-axis.
    /// @param radians The rotation amount in radians.
    static Matrix4f rotation_z(float radians);

    /// @brief Create field-of-view perspective matrix.
    /// @param near The distance to the near plane.
    /// @param far The distance to the far plane.
    /// @param fov The angle of the field-of-view in radians.
    /// @param aspect The aspect ratio of the view as width over height.
    static Matrix4f fov_perspective(float near, float far, float fov, float aspect);

    /// @brief Get a reference to the element at the specified index.
    float & operator[](Index);

    /// @brief Get a copy of the element at the specified index.
    float operator[](Index) const;

    /// @brief Multiply and assign with another matrix.
    Matrix4f& operator*=(const Matrix4f &);

    /// @brief Compute the inverse matrix of this matrix.
    Matrix4f inverse() const;
};

/// @brief Multiply two matrices together.
Matrix4f operator*(const Matrix4f &, const Matrix4f &);

/// @brief Multiply a matrix with a 3D vector. This is useful to apply a transformation matrix to a position vector.
Vector3f operator*(const Matrix4f &, const Vector3f &);

#endif
