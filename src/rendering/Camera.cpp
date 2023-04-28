#include "Camera.hpp"

#include <math.h>

Camera::Camera(float aspectRatio)
{
    projection = Matrix4f::fov_perspective(1.0f, 1000.f, M_PI_2, aspectRatio);
}

Matrix4f Camera::getProjection() const
{
    return projection;
}

Matrix4f Camera::getView() const
{
    return transform.getMatrix().inverse();
}
