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
    models[ModelKey::rock] = modelLoader.load("asset/rock.fbx");
    models[ModelKey::target] = modelLoader.load("asset/target.fbx");
    models[ModelKey::frozen] = modelLoader.load("asset/frozen.fbx");

    // Load textures

    TextureLoader textureLoader;
    textures[TextureKey::curlingStoneRed] = textureLoader.load("asset/curling_stone_red.jpg");
    textures[TextureKey::curlingStoneBlue] = textureLoader.load("asset/curling_stone_blue.jpg");
    textures[TextureKey::ice] = textureLoader.load("asset/ice.jpg");
    textures[TextureKey::rock] = textureLoader.load("asset/rock.jpg");
    textures[TextureKey::target] = textureLoader.load("asset/target.jpg");

    // Load materials

    Shader *defaultShader = &ShaderLibrary::shared().defaultShader;
    Shader *effectShader = &ShaderLibrary::shared().effectShader;
    materials[MaterialKey::defaultCurlingStoneRed] = std::make_unique<Material>(defaultShader, getTexture(TextureKey::curlingStoneRed));
    materials[MaterialKey::defaultCurlingStoneBlue] = std::make_unique<Material>(defaultShader, getTexture(TextureKey::curlingStoneBlue));
    materials[MaterialKey::defaultIce] = std::make_unique<Material>(defaultShader, getTexture(TextureKey::ice));
    materials[MaterialKey::defaultRock] = std::make_unique<Material>(defaultShader, getTexture(TextureKey::rock));
    materials[MaterialKey::defaultTarget] = std::make_unique<Material>(defaultShader, getTexture(TextureKey::target));
    materials[MaterialKey::effectFreezing] = std::make_unique<Material>(effectShader, getTexture(TextureKey::ice));
}

AssetLibrary::AssetLibrary()
{}
