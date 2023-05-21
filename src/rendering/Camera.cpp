#include "Camera.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(float aspectRatio)
{
    projection = Matrix4f::fov_perspective(100.0f, 10000.f, 45.f * M_PI / 180.f, aspectRatio);
}

Matrix4f Camera::getProjection() const
{
    return projection;
}

Matrix4f Camera::getView() const
{
    return transform.getMatrix().inverse();
}
