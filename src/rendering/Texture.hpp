#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGL.h"

class Texture
{
    public:
        Texture(int width, int height, unsigned char *data);

        Texture(Texture &) = delete;
        Texture & operator=(Texture &) = delete;

        ~Texture();

        void bind() const;

    private:
        int width;
        int height;
        GLuint texture;
};

#endif
