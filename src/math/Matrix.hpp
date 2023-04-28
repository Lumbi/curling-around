#ifndef MATRIX_H
#define MATRIX_H

#include "language/Index.hpp"

struct Matrix4f
{
    float data[16];

    static Matrix4f identity();

    static Matrix4f translation(float tx, float ty, float tz);

    static Matrix4f rotation_x(float radians);
    static Matrix4f rotation_y(float radians);
    static Matrix4f rotation_z(float radians);

    static Matrix4f fov_perspective(float near, float far, float fov, float aspect);

    float & operator[](Index);
    float operator[](Index) const;

    Matrix4f& operator*=(const Matrix4f&);

    Matrix4f inverse() const;
};

Matrix4f operator*(const Matrix4f& , const Matrix4f&);

#endif
