#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "rendering/Shader.hpp"

class ShaderLibrary
{
    public:
        static ShaderLibrary & shared();

        ShaderLibrary(ShaderLibrary &) = delete;
        ShaderLibrary& operator=(ShaderLibrary &) = delete;

        Shader defaultShader;

    private:
        ShaderLibrary();
};

#endif
