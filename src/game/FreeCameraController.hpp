#ifndef FREE_CAMERA_CONTROLLER_H
#define FREE_CAMERA_CONTROLLER_H

class Camera;

/// @brief A class to control the camera freely in 3D space. Used for debugging.
class FreeCameraController {
    public:
        /// @brief Initialize the controller.
        /// @param Camera The camera to control.
        FreeCameraController(Camera *Camera);

        /// @brief Update the controller for a single frame to move the camera.
        void update();

    private:
        Camera *camera;
};

#endif
