#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/Matrix.hpp"

class Shader;
class Texture;
class Scene;

/// @brief An abstraction for a material to be applied to a mesh.
class Material {
    public:
        /// @brief Initialize the material.
        /// @param shader The shader to use for this material.
        /// @param texture The texture to use for this material.
        Material(Shader *shader, Texture *texture);

        /// @brief Use this material during the subsequent rendering of meshes.
        /// @param projection The projection matrix.
        /// @param view The view matrix.
        /// @param model The model matrix (in world space).
        void use(const Matrix4f &projection, const Matrix4f &view, const Matrix4f &model) const;

    private:
        // NOTE: The material does not have ownership over the shader and texture.
        //       These should be managed elsewhere.
        Shader *shader;
        Texture *texture;
};

#endif
