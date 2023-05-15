#include "Material.hpp"

#include "rendering/Shader.hpp"
#include "rendering/Texture.hpp"
#include "asset/ShaderLibrary.hpp"
#include "asset/AssetLibrary.hpp"

Material::Material(Shader *shader, Texture *texture)
    : shader(shader), texture(texture)
{}

void Material::use(const Matrix4f& projection, const Matrix4f& view, const Matrix4f &model) const
{
    if (shader && texture) {
        shader->setModelUniform(model);
        shader->setProjectionUniform(projection);
        shader->setViewUniform(view);
        shader->setTexture0(*texture);
        shader->use();
    }
}
