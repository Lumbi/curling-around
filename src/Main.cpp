#include <iostream>
#include <memory>

#include "OpenGL.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Time.hpp"
#include "math/Vector.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"
#include "physics/Physics.hpp"
#include "input/Keyboard.hpp"
#include "input/Input.hpp"
#include "asset/AssetLibrary.hpp"
#include "game/Parameter.hpp"
#include "game/Scene.hpp"
#include "game/Actor.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/actors/CurlingStone.hpp"
#include "game/actors/Obstacle.hpp"
#include "game/PlayerController.hpp"

int main(int argc, char* argv[])
{
    Parameter::shared().load();

    const int WINDOW_WIDTH = 960;
    const int WINDOW_HEIGHT = 720;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Curling Around!", // title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // position
        WINDOW_WIDTH, WINDOW_HEIGHT, // size
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL // flags
    );

    // Initialize the camera
    float aspectRatio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    auto camera = std::make_unique<Camera>(aspectRatio);

    // Initialize the renderer
    Renderer renderer(window, camera.get());

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

    if (GLEW_OK != glewInit())
    {
        // GLEW failed!
        return -1;
    }

    // V-sync
    if (SDL_GL_SetSwapInterval(1) != 0) {
        printf("Warnning: Could not enable v-sync: %s\n", SDL_GetError());
    }

    // Face culling
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    AssetLibrary::shared().load();

    auto scene = std::make_unique<Scene>();

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

    PlayerController playerController(scene.get(), camera.get());

    const float targetFramesPerSecond = 60.f;
    const float targetFrameTimeInSeconds = 1.f / targetFramesPerSecond;

    while (running)
    {
        Time::shared().beginFrame();
        {
            Parameter::shared().update();

            Input::shared().update();
            if (Input::shared().quit) {
                running = false;
            }

            Physics::shared().update();
            playerController.update();
            scene->update();

            renderer.begin();
            scene->draw(renderer);
            renderer.end();
        }
        Time::shared().endFrame();

        if (Time::shared().deltaTime < targetFrameTimeInSeconds) {
            Time::shared().sleep(targetFrameTimeInSeconds - Time::shared().deltaTime);
        }
    }

    SDL_Quit();

    return 0;
}
