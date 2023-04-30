#include "Matrix.hpp"

#include <math.h>
#include <algorithm>

float & Matrix4f::operator[](Index i)
{
    return data[i];
}

float Matrix4f::operator[](Index i) const
{
    return data[i];
}

Matrix4f Matrix4f::identity()
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::translation(float tx, float ty, float tz)
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    };
}

Matrix4f Matrix4f::rotation_x(float radians)
{
    const float c = cos(radians);
    const float s = sin(radians);
    return {
        1,  0,  0,  0,
        0,  c, -s,  0,
        0,  s,  c,  0,
        0,  0,  0,  1
    };
}

Matrix4f Matrix4f::rotation_y(float radians)
{
    const float c = cos(radians);
    const float s = sin(radians);
    return {
        c,  0,  s,  0,
        0,  1,  0,  0,
       -s,  0,  c,  0,
        0,  0,  0,  1
    };
}

Matrix4f Matrix4f::rotation_z(float radians)
{
    const float c = cos(radians);
    const float s = sin(radians);
    return {
        c, -s,  0,  0,
        s,  c,  0,  0,
        0,  0,  1,  0,
        0,  0,  0,  1
    };
}

Matrix4f Matrix4f::fov_perspective(float near, float far, float fov, float aspect)
{
    const float y = 1 / tan(fov / 2.f);
    const float x = y / aspect;
    const float range = near - far;
    return {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, (far + near) / range, -1,
        0, 0, (2 * far * near) / range, 0
    };
}

Matrix4f operator*(const Matrix4f& lhs, const Matrix4f& rhs)
{
    return {                                                                            //row, col
        lhs[ 0] * rhs[ 0] + lhs[ 1] * rhs[ 4] + lhs[ 2] * rhs[ 8] + lhs[ 3] * rhs[12],  //  0, 0
        lhs[ 0] * rhs[ 1] + lhs[ 1] * rhs[ 5] + lhs[ 2] * rhs[ 9] + lhs[ 3] * rhs[13],  //  0, 1
        lhs[ 0] * rhs[ 2] + lhs[ 1] * rhs[ 6] + lhs[ 2] * rhs[10] + lhs[ 3] * rhs[14],  //  0, 2
        lhs[ 0] * rhs[ 3] + lhs[ 1] * rhs[ 7] + lhs[ 2] * rhs[11] + lhs[ 3] * rhs[15],  //  0, 3

        lhs[ 4] * rhs[ 0] + lhs[ 5] * rhs[ 4] + lhs[ 6] * rhs[ 8] + lhs[ 7] * rhs[12],  //  1, 0
        lhs[ 4] * rhs[ 1] + lhs[ 5] * rhs[ 5] + lhs[ 6] * rhs[ 9] + lhs[ 7] * rhs[13],  //  1, 1
        lhs[ 4] * rhs[ 2] + lhs[ 5] * rhs[ 6] + lhs[ 6] * rhs[10] + lhs[ 7] * rhs[14],  //  1, 2
        lhs[ 4] * rhs[ 3] + lhs[ 5] * rhs[ 7] + lhs[ 6] * rhs[11] + lhs[ 7] * rhs[15],  //  1, 2

        lhs[ 8] * rhs[ 0] + lhs[ 9] * rhs[ 4] + lhs[10] * rhs[ 8] + lhs[11] * rhs[12],  //  2, 0
        lhs[ 8] * rhs[ 1] + lhs[ 9] * rhs[ 5] + lhs[10] * rhs[ 9] + lhs[11] * rhs[13],  //  2, 1
        lhs[ 8] * rhs[ 2] + lhs[ 9] * rhs[ 6] + lhs[10] * rhs[10] + lhs[11] * rhs[14],  //  2, 2
        lhs[ 8] * rhs[ 3] + lhs[ 9] * rhs[ 7] + lhs[10] * rhs[11] + lhs[11] * rhs[15],  //  2, 3

        lhs[12] * rhs[ 0] + lhs[13] * rhs[ 4] + lhs[14] * rhs[ 8] + lhs[15] * rhs[12],  //  3, 0
        lhs[12] * rhs[ 1] + lhs[13] * rhs[ 5] + lhs[14] * rhs[ 9] + lhs[15] * rhs[13],  //  3, 1
        lhs[12] * rhs[ 2] + lhs[13] * rhs[ 6] + lhs[14] * rhs[10] + lhs[15] * rhs[14],  //  3, 2
        lhs[12] * rhs[ 3] + lhs[13] * rhs[ 7] + lhs[14] * rhs[11] + lhs[15] * rhs[15]   //  3, 3
    };
}

Matrix4f& Matrix4f::operator*=(const Matrix4f& rhs)
{
    Matrix4f result = (*this) * rhs;
    std::copy(result.data, result.data + 16, data);
    return *this;
}

Vector3f operator*(const Matrix4f &lhs, const Vector3f &rhs)
{
    return {
        lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3],
        lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7],
        lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11]
    };
}

Matrix4f Matrix4f::inverse() const
{
    Matrix4f inv;
    const float* m = this->data;

    inv[0] =   m[ 5] * m[10] * m[15] -
               m[ 5] * m[11] * m[14] -
               m[ 9] * m[ 6] * m[15] +
               m[ 9] * m[ 7] * m[14] +
               m[13] * m[ 6] * m[11] -
               m[13] * m[ 7] * m[10];

    inv[4] =  -m[ 4] * m[10] * m[15] +
               m[ 4] * m[11] * m[14] +
               m[ 8] * m[ 6] * m[15] -
               m[ 8] * m[ 7] * m[14] -
               m[12] * m[ 6] * m[11] +
               m[12] * m[ 7] * m[10];

    inv[8] =   m[ 4] * m[ 9] * m[15] -
               m[ 4] * m[11] * m[13] -
               m[ 8] * m[ 5] * m[15] +
               m[ 8] * m[ 7] * m[13] +
               m[12] * m[ 5] * m[11] -
               m[12] * m[ 7] * m[ 9];

    inv[12] = -m[ 4] * m[ 9] * m[14] +
               m[ 4] * m[10] * m[13] +
               m[ 8] * m[ 5] * m[14] -
               m[ 8] * m[ 6] * m[13] -
               m[12] * m[ 5] * m[10] +
               m[12] * m[ 6] * m[ 9];

    inv[1] =  -m[ 1] * m[10] * m[15] +
               m[ 1] * m[11] * m[14] +
               m[ 9] * m[ 2] * m[15] -
               m[ 9] * m[ 3] * m[14] -
               m[13] * m[ 2] * m[11] +
               m[13] * m[ 3] * m[10];

    inv[5] =   m[ 0] * m[10] * m[15] -
               m[ 0] * m[11] * m[14] -
               m[ 8] * m[ 2] * m[15] +
               m[ 8] * m[ 3] * m[14] +
               m[12] * m[ 2] * m[11] -
               m[12] * m[ 3] * m[10];

    inv[9] =  -m[0 ] * m[ 9] * m[15] +
               m[0 ] * m[11] * m[13] +
               m[8 ] * m[ 1] * m[15] -
               m[8 ] * m[ 3] * m[13] -
               m[12] * m[ 1] * m[11] +
               m[12] * m[ 3] * m[ 9];

    inv[13] =  m[ 0] * m[ 9] * m[14] -
               m[ 0] * m[10] * m[13] -
               m[ 8] * m[ 1] * m[14] +
               m[ 8] * m[ 2] * m[13] +
               m[12] * m[ 1] * m[10] -
               m[12] * m[ 2] * m[ 9];

    inv[2] =   m[ 1] * m[ 6] * m[15] -
               m[ 1] * m[ 7] * m[14] -
               m[ 5] * m[ 2] * m[15] +
               m[ 5] * m[ 3] * m[14] +
               m[13] * m[ 2] * m[ 7] -
               m[13] * m[ 3] * m[ 6];

    inv[6] =  -m[ 0] * m[ 6] * m[15] +
               m[ 0] * m[ 7] * m[14] +
               m[ 4] * m[ 2] * m[15] -
               m[ 4] * m[ 3] * m[14] -
               m[12] * m[ 2] * m[ 7] +
               m[12] * m[ 3] * m[ 6];

    inv[10] =  m[ 0] * m[ 5] * m[15] -
               m[ 0] * m[ 7] * m[13] -
               m[ 4] * m[ 1] * m[15] +
               m[ 4] * m[ 3] * m[13] +
               m[12] * m[ 1] * m[ 7] -
               m[12] * m[ 3] * m[ 5];

    inv[14] = -m[ 0] * m[ 5] * m[14] +
               m[ 0] * m[ 6] * m[13] +
               m[ 4] * m[ 1] * m[14] -
               m[ 4] * m[ 2] * m[13] -
               m[12] * m[ 1] * m[ 6] +
               m[12] * m[ 2] * m[ 5];

    inv[3] =  -m[ 1] * m[ 6] * m[11] +
               m[ 1] * m[ 7] * m[10] +
               m[ 5] * m[ 2] * m[11] -
               m[ 5] * m[ 3] * m[10] -
               m[ 9] * m[ 2] * m[ 7] +
               m[ 9] * m[ 3] * m[ 6];

    inv[7] =   m[ 0] * m[ 6] * m[11] -
               m[ 0] * m[ 7] * m[10] -
               m[ 4] * m[ 2] * m[11] +
               m[ 4] * m[ 3] * m[10] +
               m[ 8] * m[ 2] * m[ 7] -
               m[ 8] * m[ 3] * m[ 6];

    inv[11] = -m[ 0] * m[ 5] * m[11] +
               m[ 0] * m[ 7] * m[ 9] +
               m[ 4] * m[ 1] * m[11] -
               m[ 4] * m[ 3] * m[ 9] -
               m[ 8] * m[ 1] * m[ 7] +
               m[ 8] * m[ 3] * m[ 5];

    inv[15] =  m[ 0] * m[ 5] * m[10] -
               m[ 0] * m[ 6] * m[ 9] -
               m[ 4] * m[ 1] * m[10] +
               m[ 4] * m[ 2] * m[ 9] +
               m[ 8] * m[ 1] * m[ 6] -
               m[ 8] * m[ 2] * m[ 5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return *this;

    det = 1.f / det;

    for (int i = 0; i < 16; i++)
        inv[i] *= det;

    return inv;
}
