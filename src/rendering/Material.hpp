#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/Matrix.hpp"

class Shader;
class Texture;
class Scene;

class Material {
    public:
        Material(Shader *, Texture *);

        void use(const Matrix4f &projection, const Matrix4f &view, const Matrix4f &model) const;

    private:
        Shader *shader;
        Texture *texture;
};

#endif
