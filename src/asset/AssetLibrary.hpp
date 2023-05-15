#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <unordered_map>

class Model;
class Texture;

class AssetLibrary {
    public:
        static AssetLibrary & shared();

        AssetLibrary(AssetLibrary &) = delete;
        AssetLibrary& operator=(AssetLibrary &) = delete;

        enum class ModelKey {
            curlingStone
        };

        Model * getModel(ModelKey);


        enum class TextureKey {
            curlingStone
        };

        Texture * getTexture(TextureKey);

    public:
        void load();

    private:
        AssetLibrary();

        std::unordered_map<ModelKey, std::unique_ptr<Model>> models;
        std::unordered_map<TextureKey, std::unique_ptr<Texture>> textures;
};

#endif
