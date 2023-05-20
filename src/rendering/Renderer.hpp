#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "math/Matrix.hpp"
#include "Camera.hpp"

class Model;
class Material;

/// @brief A class to handle rendering with a window and camera.
class Renderer {
    public:
        /// @brief Initialize the renderer.
        /// @param window The window used to get the viewport size.
        /// @param camera The camera used to get the projection.
        Renderer(SDL_Window *window, Camera *camera);

        /// @brief Begin a rendering operation.
        void begin();

        /// @brief Render a model. Must be called between Renderer::begin() and Renderer::end().
        /// @param model The model to render.
        /// @param material The texture to apply to the model.
        /// @param transform The transform to apply to the model.
        void render(Model &model, Material &material, const Matrix4f &transform);

        /// @brief End a rendering operation. Must be called after Renderer::begin().
        void end();

    private:
        SDL_Window *window;
        Camera *camera;
};


#endif