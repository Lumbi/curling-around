#ifndef VECTOR_H
#define VECTOR_H

struct Vector3f
{
    float x;
    float y;
    float z;

    static const Vector3f zero;

    Vector3f& operator+=(const Vector3f &);
};

Vector3f operator+(const Vector3f &, const Vector3f &);

#endif
