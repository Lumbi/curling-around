#include "AssetLibrary.hpp"

#include "ShaderLibrary.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Model.hpp"
#include "ModelLoader.hpp"
#include "rendering/Texture.hpp"
#include "TextureLoader.hpp"
#include "rendering/Material.hpp"

AssetLibrary & AssetLibrary::shared()
{
    static AssetLibrary instance;
    return instance;
}

Model * AssetLibrary::getModel(AssetLibrary::ModelKey key)
{
    return models[key].get();
}

Texture * AssetLibrary::getTexture(AssetLibrary::TextureKey key)
{
    return textures[key].get();
}

Material * AssetLibrary::getMaterial(MaterialKey key)
{
    return materials[key].get();
}

void AssetLibrary::load()
{
    // Load models

    ModelLoader modelLoader;
    models[ModelKey::curlingStone] = modelLoader.load("asset/curling_stone.fbx");
    models[ModelKey::field] = modelLoader.load("asset/field.fbx");

    // Load textures

    TextureLoader textureLoader;
    textures[TextureKey::curlingStone] = textureLoader.load("asset/curling_stone_tex_diffuse.jpg");
    textures[TextureKey::ice] = textureLoader.load("asset/ice.jpg");

    // Load materials

    materials[MaterialKey::defaultCurlingStone] = std::make_unique<Material>(
        &ShaderLibrary::shared().defaultShader,
        getTexture(TextureKey::curlingStone)
    );

    materials[MaterialKey::defaultIce] = std::make_unique<Material>(
        &ShaderLibrary::shared().defaultShader,
        getTexture(TextureKey::ice)
    );
}

AssetLibrary::AssetLibrary()
{}
