#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <unordered_map>
#include <memory>

class Model;
class Texture;
class Material;

/// @brief A singleton to manage the loaded game assets.
class AssetLibrary {
    public:
        /// @brief Get the shared singleton instance.
        static AssetLibrary & shared();

        /// @brief A key to access a model in the library.
        enum class ModelKey {
            curlingStone,
            field,
            rock,
            target,
            frozen
        };

        /// @brief Get the model at the specified key.
        Model * getModel(ModelKey);

        /// @brief A key to access a texture in the library.
        enum class TextureKey {
            curlingStoneRed,
            curlingStoneBlue,
            ice,
            rock,
            target
        };

        /// @brief Get the texture at the specified key.
        Texture * getTexture(TextureKey);

        /// @brief A key to access a material in the library.
        enum class MaterialKey {
            defaultCurlingStoneRed,
            defaultCurlingStoneBlue,
            defaultIce,
            defaultRock,
            defaultTarget
        };

        /// @brief Get the material at the specified key.
        Material * getMaterial(MaterialKey);

        // Disable the copy-constructor and copy-assignment operator.
        AssetLibrary(AssetLibrary &) = delete;
        AssetLibrary & operator=(AssetLibrary &) = delete;

    public:
        /// @brief Load all assets into the library.
        void load();

    private:
        AssetLibrary();

        std::unordered_map<ModelKey, std::unique_ptr<Model>> models;
        std::unordered_map<TextureKey, std::unique_ptr<Texture>> textures;
        std::unordered_map<MaterialKey, std::unique_ptr<Material>> materials;
};

#endif
