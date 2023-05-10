#include "Vector.hpp"

const Vector3f Vector3f::zero = { 0, 0, 0 };

const Vector3f Vector3f::forward = { 0, 0, -1 };

Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Vector3f& Vector3f::operator+=(const Vector3f &rhs)
{
    this->x += rhs.x; this->y += rhs.y; this->z += rhs.z;
    return *this;
}
