#ifndef VECTOR_H
#define VECTOR_H

/// @brief A 2D vector of floats.
struct Vector2f
{
    float x;
    float y;
};

/// @brief A 3D vector of floats.
struct Vector3f
{
    float x;
    float y;
    float z;

    /// @brief A vector at { 0 , 0 }
    static const Vector3f zero;

    /// @brief Add and assign this vector with another vector.
    Vector3f& operator+=(const Vector3f &);

    /// @brief Multiply and assign this vector by a scalar.
    Vector3f& operator*=(float);

    /// @brief Get the length (magnitude) of the vector.
    float length() const;
};

/// @brief Add two vectors.
Vector3f operator+(const Vector3f &, const Vector3f &);

/// @brief Substract two vectors.
Vector3f operator-(const Vector3f &, const Vector3f &);

/// @brief Multiply a vevtor by a scalar.
Vector3f operator*(const Vector3f &, float);

/// @brief Multiply a vevtor by a scalar.
Vector3f operator*(float, const Vector3f &);

/// @brief Normalize a vector.
Vector3f normalize(const Vector3f &);

/// @brief Compute the dot product between two vectors.
float dot(const Vector3f &, const Vector3f &);

/// @brief Compute the distance between two vectors representing positions.
float distance(const Vector3f &, const Vector3f &);

/// @brief Interpolate linearly between two vectors.
/// @param a The start vector.
/// @param b The end vector.
/// @param t The interpolation value between 0 and 1.
/// @return The intermediate vector interpolated between the start vector and the end vector.
Vector3f lerp(const Vector3f &a, const Vector3f &b, float t);

#endif
