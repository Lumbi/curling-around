#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <unordered_map>
#include <memory>

class Model;
class Texture;
class Material;

class AssetLibrary {
    public:
        static AssetLibrary & shared();

        AssetLibrary(AssetLibrary &) = delete;
        AssetLibrary& operator=(AssetLibrary &) = delete;

        enum class ModelKey {
            curlingStone,
            field,
            rock,
            target
        };

        Model * getModel(ModelKey);

        enum class TextureKey {
            curlingStoneRed,
            curlingStoneBlue,
            ice,
            target
        };

        Texture * getTexture(TextureKey);

        enum class MaterialKey {
            defaultCurlingStoneRed,
            defaultCurlingStoneBlue,
            defaultIce,
            defaultTarget
        };

        Material * getMaterial(MaterialKey);

    public:
        void load();

    private:
        AssetLibrary();

        std::unordered_map<ModelKey, std::unique_ptr<Model>> models;
        std::unordered_map<TextureKey, std::unique_ptr<Texture>> textures;
        std::unordered_map<MaterialKey, std::unique_ptr<Material>> materials;
};

#endif
