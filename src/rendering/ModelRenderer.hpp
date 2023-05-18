#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "math/Matrix.hpp"
#include "Model.hpp"

class Material;

/// @brief A class responsible for rendering a model.
class ModelRenderer
{
    public:
        /// @brief Render the provided model if with specified material and transformation matrices.
        /// @param model The model to render.
        /// @param material The material to apply to the model.
        /// @param projectionMatrix The projection matrix to use during rendering.
        /// @param viewMatrix The view matrix to use during rendering.
        /// @param modelMatrix The model matrix to transform the model during rendering.
        void render(
            const Model &model,
            const Material &material,
            const Matrix4f &projectionMatrix,
            const Matrix4f &viewMatrix,
            const Matrix4f &modelMatrix
        );

    private:
        void render(
            const Model &model,
            const Material &material,
            const Matrix4f &projectionMatrix,
            const Matrix4f &viewMatrix,
            const Matrix4f &modelMatrix,
            Model::Node &node
        );
};

#endif
