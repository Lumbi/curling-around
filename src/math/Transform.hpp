#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.hpp"
#include "Matrix.hpp"

class Transform
{
    public:
        Transform();

        Vector3f getPosition() const;
        void setPosition(const Vector3f &);
        void translateBy(const Vector3f &);

        Vector3f getRotation() const;
        void setRotation(const Vector3f &);
        void rotateBy(const Vector3f &);

        Matrix4f getMatrix() const;

    private:
        Vector3f position;
        Vector3f rotation;
};

#endif