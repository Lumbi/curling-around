#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "math/Matrix.hpp"

#include "Model.hpp"

class Material;

class ModelRenderer
{
    public:
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
