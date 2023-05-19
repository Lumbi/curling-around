#include "FreeCameraController.hpp"

#include "input/Input.hpp"
#include "input/Keyboard.hpp"
#include "math/Vector.hpp"
#include "rendering/Camera.hpp"

FreeCameraController::FreeCameraController(Camera *camera)
    : camera(camera)
{}

void FreeCameraController::update()
{
    if (!camera) { return; }

    Keyboard &keyboard = Input::shared().keyboard;
    if (keyboard.isPressed(SDLK_UP)) { camera->transform.rotateBy({ -0.1f, 0, 0 }); }
    if (keyboard.isPressed(SDLK_DOWN)) { camera->transform.rotateBy({ 0.1f, 0, 0 }); }
    if (keyboard.isPressed(SDLK_LEFT)) { camera->transform.rotateBy({ 0, -0.1f, 0 }); }
    if (keyboard.isPressed(SDLK_RIGHT)) { camera->transform.rotateBy({ 0, 0.1f, 0 }); }

    float cameraSpeed = 30.0f;
    if (keyboard.isPressed(SDLK_LSHIFT)) {
        cameraSpeed = 10.0f;
    }
    Vector3f cameraMovement = Vector3f::zero;
    if (keyboard.isPressed(SDLK_a)) { cameraMovement.x -= cameraSpeed; }
    if (keyboard.isPressed(SDLK_d)) { cameraMovement.x += cameraSpeed; }
    if (keyboard.isPressed(SDLK_w)) { cameraMovement.z -= cameraSpeed; }
    if (keyboard.isPressed(SDLK_s)) { cameraMovement.z += cameraSpeed; }
    if (cameraMovement.x != 0 || cameraMovement.y != 0 || cameraMovement.z != 0) {
        cameraMovement = camera->transform.getMatrix().inverse() * cameraMovement;
        camera->transform.translateBy(cameraMovement);
    }

    if (keyboard.isPressed(SDLK_q)) { camera->transform.translateBy({ 0, -cameraSpeed, 0}); }
    if (keyboard.isPressed(SDLK_e)) { camera->transform.translateBy({ 0, cameraSpeed, 0}); }
}
