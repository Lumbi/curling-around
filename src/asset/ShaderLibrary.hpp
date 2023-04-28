#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "rendering/Shader.hpp"

class ShaderLibrary
{
    public:
        ShaderLibrary();

        ShaderLibrary(ShaderLibrary &) = delete;
        ShaderLibrary& operator=(ShaderLibrary &) = delete;

        Shader defaultShader;
};

#endif
