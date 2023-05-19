#include <iostream>
#include <memory>

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include "Time.hpp"
#include "math/Vector.hpp"
#include "rendering/Camera.hpp"
#include "physics/Physics.hpp"
#include "input/Keyboard.hpp"
#include "input/Input.hpp"
#include "asset/AssetLibrary.hpp"
#include "game/Scene.hpp"
#include "game/Actor.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/actors/CurlingStone.hpp"
#include "game/actors/Obstacle.hpp"
#include "game/PlayerController.hpp"

int main()
{
    const int WINDOW_WIDTH = 960;
    const int WINDOW_HEIGHT = 720;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Curling Around!", // title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // position
        WINDOW_WIDTH, WINDOW_HEIGHT, // size
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL // flags
    );

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("Error: Failed to create OpenGL context: %s\n", SDL_GetError());
        return -1;
    }
    printf("Using OpenGL version %s\n", glGetString(GL_VERSION));

    // V-sync
    if (SDL_GL_SetSwapInterval(1) != 0) {
        printf("Warnning: Could not enable v-sync: %s\n", SDL_GetError());
    }

    glShadeModel(GL_SMOOTH);

    // Face culling
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    AssetLibrary::shared().load();

    auto scene = std::make_unique<Scene>();

    // Camera
    {
        float aspectRatio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
        auto camera = std::make_unique<Camera>(aspectRatio);
        scene->setCamera(std::move(camera));
    }

    // Level
    {
        // Field
        auto fieldActor = std::make_unique<Actor>();
        fieldActor->attachComponent(
            std::make_unique<ModelComponent>(
                AssetLibrary::shared().getModel(AssetLibrary::ModelKey::field),
                AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultIce)
            )
        );
        scene->getRoot()->addChild(std::move(fieldActor));

        // Target
        auto targetActor = std::make_unique<Actor>();
        targetActor->attachComponent(
            std::make_unique<ModelComponent>(
                AssetLibrary::shared().getModel(AssetLibrary::ModelKey::target),
                AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultTarget)
            )
        );
        scene->getRoot()->addChild(std::move(targetActor));

        // Obstacles
        scene->getRoot()->addChild(std::make_unique<Obstacle>(Vector3f(1000.f,  0.f,   0.f)));
        scene->getRoot()->addChild(std::make_unique<Obstacle>(Vector3f(500.f,  0.f, 1100.f)));
        scene->getRoot()->addChild(std::make_unique<Obstacle>(Vector3f(-300.f,  0.f,  600.f)));
        scene->getRoot()->addChild(std::make_unique<Obstacle>(Vector3f(700.f,  0.f, -700.f)));
        scene->getRoot()->addChild(std::make_unique<Obstacle>(Vector3f(-500.f,  0.f, -800.f)));
    }

    bool running = true;

    Keyboard &keyboard = Input::shared().keyboard;

    PlayerController playerController(scene.get());

    const float targetFramesPerSecond = 60.f;
    const float targetFrameTimeInSeconds = 1.f / targetFramesPerSecond;

    while (running)
    {
        Time::shared().beginFrame();

        Input::shared().update();
        if (Input::shared().quit) {
            running = false;
        }

        Physics::shared().update();

        playerController.update();

        // Camera controls
        Camera &camera = *scene->getCamera();
        if (false) {
            if (keyboard.isPressed(SDLK_UP)) { camera.transform.rotateBy({ -0.1f, 0, 0 }); }
            if (keyboard.isPressed(SDLK_DOWN)) { camera.transform.rotateBy({ 0.1f, 0, 0 }); }
            if (keyboard.isPressed(SDLK_LEFT)) { camera.transform.rotateBy({ 0, -0.1f, 0 }); }
            if (keyboard.isPressed(SDLK_RIGHT)) { camera.transform.rotateBy({ 0, 0.1f, 0 }); }

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
                cameraMovement = camera.transform.getMatrix().inverse() * cameraMovement;
                camera.transform.translateBy(cameraMovement);
            }

            if (keyboard.isPressed(SDLK_q)) { camera.transform.translateBy({ 0, -cameraSpeed, 0}); }
            if (keyboard.isPressed(SDLK_e)) { camera.transform.translateBy({ 0, cameraSpeed, 0}); }
        }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->getRoot()->update();
        scene->getRoot()->draw(*scene.get());

        SDL_GL_SwapWindow(window);

        Time::shared().endFrame();

        if (Time::shared().deltaTime < targetFrameTimeInSeconds) {
            Time::shared().sleep(targetFrameTimeInSeconds - Time::shared().deltaTime);
        }
    }

    SDL_Quit();

    return 0;
}
