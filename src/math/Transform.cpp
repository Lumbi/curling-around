#include "Transform.hpp"

Transform::Transform()
    : position(Vector3f::zero), rotation(Vector3f::zero)
{}

Vector3f Transform::getPosition() const
{
    return position;
}

void Transform::setPosition(const Vector3f &position)
{
    this->position = position;
}

void Transform::translateBy(const Vector3f &delta)
{
    this->position += delta;
}

Vector3f Transform::getRotation() const
{
    return rotation;
}

void Transform::setRotation(const Vector3f &rotation)
{
    this->rotation = rotation;
}

void Transform::rotateBy(const Vector3f &delta)
{
    this->rotation += delta;
}

Matrix4f Transform::getMatrix() const
{
    // TODO: Support actor scaling
    return
        Matrix4f::rotation_x(rotation.x) *
        Matrix4f::rotation_y(rotation.y) *
        Matrix4f::rotation_z(rotation.z) *
        Matrix4f::translation(position.x, position.y, position.z);
}
