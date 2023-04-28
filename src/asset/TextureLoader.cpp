#include "TextureLoader.hpp"

#include "rendering/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "OpenGL.h"

std::unique_ptr<Texture> TextureLoader::load(const char *file)
{
    stbi_set_flip_vertically_on_load(true);
    int textureWidth, textureHeight, channelCount;
    stbi_uc *textureData = stbi_load(file, &textureWidth, &textureHeight, &channelCount, 0);
    if (!textureData) {
        printf("Error: failed to load texture at file '%s'\n", file);
    }

    std::unique_ptr<Texture> texture = std::make_unique<Texture>(textureWidth, textureHeight, textureData);

    stbi_image_free(textureData);

    return std::move(texture);
}
