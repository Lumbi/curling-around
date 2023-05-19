#include "Texture.hpp"

Texture::Texture(int width, int height, unsigned char *data)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0, // level-of-detail
        GL_RGB, // internal format
        width,
        height,
        0, // legacy border parameter
        GL_RGB, // texture format
        GL_UNSIGNED_BYTE, // data format (= stbi_uc)
        data
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}
