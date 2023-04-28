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

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "math/Matrix.hpp"
#include "math/Vector.hpp"
#include "rendering/Vertex.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Model.hpp"
#include "rendering/ModelRenderer.hpp"
#include "language/Index.hpp"
#include "input/Keyboard.hpp"
#include "asset/ModelLoader.hpp"
#include "asset/ShaderLibrary.hpp"

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

    // Camera
    float aspectRatio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    Camera camera(aspectRatio);
    camera.transform.setPosition({ 0, 0, 10});

    ShaderLibrary shaderLibrary;

    // Test model
    ModelLoader modelLoader;
    std::unique_ptr<Model> teapot = modelLoader.load("asset/teapot.fbx");

    ModelRenderer modelRenderer;

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

        // Camera controls

        if (keyboard.isPressed(SDLK_a)) { camera.transform.translateBy({ -0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_d)) { camera.transform.translateBy({  0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_w)) { camera.transform.translateBy({ 0, 0, -0.1f }); }
        if (keyboard.isPressed(SDLK_s)) { camera.transform.translateBy({ 0, 0,  0.1f }); }

        if (keyboard.isPressed(SDLK_UP)) { camera.transform.rotateBy({ -0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_DOWN)) { camera.transform.rotateBy({ 0.1f, 0, 0 }); }
        if (keyboard.isPressed(SDLK_LEFT)) { camera.transform.rotateBy({ 0, -0.1f, 0 }); }
        if (keyboard.isPressed(SDLK_RIGHT)) { camera.transform.rotateBy({ 0, 0.1f, 0 }); }

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader &shader = shaderLibrary.defaultShader;
        shader.setProjectionUniform(camera.getProjection());
        shader.setViewUniform(camera.getView());
        shader.use();
        modelRenderer.render(teapot.get());

        SDL_GL_SwapWindow(window);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    SDL_Quit();

    return 0;
}
