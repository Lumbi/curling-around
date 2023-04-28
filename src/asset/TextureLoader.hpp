#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <memory>

class Texture;

class TextureLoader
{
    public:
        std::unique_ptr<Texture> load(const char *file);
    private:
};

#endif
