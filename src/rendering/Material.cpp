#include "Material.hpp"

#include "Time.hpp"
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
        shader->setModel(model);
        shader->setProjection(projection);
        shader->setView(view);

        if (texture) {
            shader->setTexture0(*texture);
        }

        // TODO: Create abstraction for light and refactor this code
        shader->setGlobalLightPosition({ 10000.f, 20000.f, 0.f });

        shader->setTime(Time::shared().time);

        shader->use();
    }
}
