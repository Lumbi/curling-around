#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "math/Matrix.hpp"

class Model;

class ModelRenderer
{
    public:
        void render(const Model &model, const Matrix4f &modelMatrix);
};

#endif