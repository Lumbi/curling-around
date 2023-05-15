#include "Vector.hpp"

#include "math.h"

const Vector3f Vector3f::zero = { 0, 0, 0 };

const Vector3f Vector3f::forward = { 0, 0, -1 };

Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Vector3f operator*(const Vector3f &lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

Vector3f operator*(float lhs, const Vector3f &rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

Vector3f& Vector3f::operator+=(const Vector3f &rhs)
{
    this->x += rhs.x; this->y += rhs.y; this->z += rhs.z;
    return *this;
}

float distance(const Vector3f &first, const Vector3f &second)
{
    return sqrtf(
        (second.x - first.x) * (second.x - first.x) +
        (second.y - first.y) * (second.y - first.y) +
        (second.z - first.z) * (second.z - first.z)
    );
}
