#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "math/Matrix.hpp"

#include "Model.hpp"

class ModelRenderer
{
    public:
        void render(const Model &model, const Matrix4f &modelMatrix);

    private:
        void render(const Model &model, const Matrix4f &modelMatrix, Model::Node &node);
};

#endif
