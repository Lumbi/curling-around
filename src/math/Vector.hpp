#ifndef VECTOR_H
#define VECTOR_H

struct Vector2f
{
    float x;
    float y;
};

struct Vector3f
{
    float x;
    float y;
    float z;

    static const Vector3f zero;
    static const Vector3f forward;

    Vector3f& operator+=(const Vector3f &);
};

Vector3f operator+(const Vector3f &, const Vector3f &);

Vector3f operator*(const Vector3f &, float);
Vector3f operator*(float, const Vector3f &);

float distance(const Vector3f &, const Vector3f &);

#endif
