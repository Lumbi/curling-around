#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <memory>

class Texture;

/// @brief A class to load a texture from file.
class TextureLoader
{
    public:
        /// @brief Load the texture.
        /// @param file The path to the texture's file.
        std::unique_ptr<Texture> load(const char *file);
};

#endif
