#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "math/Transform.hpp"

/// @brief A class managing the projection and view data needed for rendering.
class Camera
{
    public:
        /// @brief The transform of this camera.
        Transform transform;

    public:
        /// @brief Initialize the camera.
        /// @param aspectRatio The aspect ratio of the field-of-view.
        explicit Camera(float aspectRatio);

        /// @brief Get the camera's projection matrix.
        Matrix4f getProjection() const;

        /// @brief Get the camera's view matrix.
        Matrix4f getView() const;

    private:
        Matrix4f projection;
};

#endif
