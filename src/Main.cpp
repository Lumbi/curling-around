#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <cmath>

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include "math/Matrix.hpp"
#include "math/Vector.hpp"
#include "rendering/Vertex.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Texture.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Model.hpp"
#include "rendering/ModelRenderer.hpp"
#include "physics/Physics.hpp"
#include "physics/PhysicsBody.hpp"
#include "language/Index.hpp"
#include "input/Keyboard.hpp"
#include "asset/TextureLoader.hpp"
#include "asset/ModelLoader.hpp"
#include "asset/ShaderLibrary.hpp"
#include "game/Scene.hpp"
#include "game/Actor.hpp"
#include "game/Component.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/components/PhysicsBodyComponent.hpp"

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Untitled 3D Game", // title
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

    // Camera
    float aspectRatio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    Camera camera(aspectRatio);
    camera.transform.setPosition({ 0, 0, 10});

    // Test model
    ModelLoader modelLoader;
    std::unique_ptr<Model> testModel = modelLoader.load("asset/curling_stone.fbx");

    // Test texture
    TextureLoader textureLoader;
    std::unique_ptr<Texture> testTexture = textureLoader.load("asset/curling_stone_tex_diffuse.jpg");

    auto scene = std::make_unique<Scene>();

    {
        auto testActor = std::make_unique<Actor>();
        testActor->attachComponent(std::make_unique<ModelComponent>(testModel.get()));
        testActor->attachComponent(std::make_unique<PhysicsBodyComponent>(PhysicsBody::makeSphere(1.0f, 1.0f)));
        // testActor->getTransform().translateBy({ 0, -100, -1000 });
        scene->getRoot()->addChild(std::move(testActor));
    }

    bool running = true;

    // Input state
    Keyboard keyboard;

    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event))
        {
            keyboard.handle(event);

            switch (event.type) {
                 case SDL_QUIT: {
                    running = false;
                    break;
                }
            }
        }

        Physics::shared()->update();

        // Camera controls
        if (keyboard.isPressed(SDLK_UP)) { camera.transform.rotateBy({ -0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_DOWN)) { camera.transform.rotateBy({ 0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_LEFT)) { camera.transform.rotateBy({ 0, -0.1f, 0 }); }
        if (keyboard.isPressed(SDLK_RIGHT)) { camera.transform.rotateBy({ 0, 0.1f, 0 }); }

        float cameraSpeed = 10.0f;
        if (keyboard.isPressed(SDLK_LSHIFT)) {
            cameraSpeed = 3.0f;
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

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: Move shader to 'Material' but link camera somehow
        Shader &shader = ShaderLibrary::instance().defaultShader;
        shader.setProjectionUniform(camera.getProjection());
        shader.setViewUniform(camera.getView());
        shader.setTexture0(*testTexture);
        shader.use();

        scene->getRoot()->update();
        scene->getRoot()->draw();

        SDL_GL_SwapWindow(window);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    SDL_Quit();

    return 0;
}
