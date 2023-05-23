#ifndef SHADER_H
#define SHADER_H

#include "OpenGL.h"

class Vector3f;
class Matrix4f;
class Texture;

/// @brief A class to encapsulate a vertex shader, fragment shader and the associated shader program.
class Shader
{
    public:
        /// @brief Initialize a shader.
        /// @param vertexShaderSource The GLSL source for the vertex shader.
        /// @param fragmentShaderSource The GLSL source for the fragment shader.
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        // Disable copy-constructor and copy-assignment operator.
        Shader(Shader &) = delete;
        Shader& operator=(Shader &) = delete;

        /// @brief Destroy the shader and framgent shader.
        ~Shader();

        /// @brief Set the projection matrix uniform on this shader.
        void setProjection(const Matrix4f &);

        /// @brief Set the view matrix uniform on this shader.
        void setView(const Matrix4f &);

        /// @brief Set the model matrix uniform on this shader.
        void setModel(const Matrix4f &);

        /// @brief Set the texture at index 0 uniform on this shader.
        void setTexture0(const Texture &);

        /// @brief Set global light position uniform on this shader.
        void setGlobalLightPosition(const Vector3f &);

        /// @brief Set the time uniform on this shader.
        void setTime(float);

        /// @brief Use this shader for subsequent rendering calls.
        void use();

    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
};

#endif
