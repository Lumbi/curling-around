#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGL.h"

/// @brief A class to manage a 2D texture data.
class Texture
{
    public:
        /// @brief Initialize the texture.
        /// @param width Width of the texture in pixels.
        /// @param height Height of the texture in pixels.
        /// @param data The texture data. Currently only supports 8 bit per component RGB format.
        Texture(int width, int height, unsigned char *data);

        // Disable copy-constructor and copy-assignment operator.
        Texture(Texture &) = delete;
        Texture & operator=(Texture &) = delete;

        /// @brief Destroy the texture.
        ~Texture();

        /// @brief Bind the texture to the active texture.
        void bind() const;

    private:
        int width;
        int height;
        GLuint texture;
};

#endif
