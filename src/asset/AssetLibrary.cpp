#include "AssetLibrary.hpp"

#include "rendering/Mesh.hpp"
#include "rendering/Model.hpp"
#include "ModelLoader.hpp"
#include "rendering/Texture.hpp"
#include "TextureLoader.hpp"

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

void AssetLibrary::load()
{
    ModelLoader modelLoader;
    models[ModelKey::curlingStone] = modelLoader.load("asset/curling_stone.fbx");

    TextureLoader textureLoader;
    textures[TextureKey::curlingStone] = textureLoader.load("asset/curling_stone_tex_diffuse.jpg");
}

AssetLibrary::AssetLibrary()
{}
