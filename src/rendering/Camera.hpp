#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "math/Transform.hpp"

class Camera
{
    public:
        Transform transform;

    public:
        explicit Camera(float aspectRatio);

        Matrix4f getProjection() const;
        Matrix4f getView() const;

    private:
        Matrix4f projection;
};

#endif
