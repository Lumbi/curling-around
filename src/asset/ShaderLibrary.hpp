#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "rendering/Shader.hpp"

/// @brief A singleton to manage shaders.
class ShaderLibrary
{
    public:
        /// @brief Get the shared singleton instance.
        static ShaderLibrary & shared();

        /// @brief A default shader with basic texture and lighting support.
        Shader defaultShader;

        // Disable the copy-constructor and copy-assignment operator.
        ShaderLibrary(ShaderLibrary &) = delete;
        ShaderLibrary& operator=(ShaderLibrary &) = delete;

    private:
        ShaderLibrary();
};

#endif
