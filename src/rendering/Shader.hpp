#ifndef SHADER_H
#define SHADER_H

#include "OpenGL.h"

class Matrix4f;
class Texture;

class Shader
{
    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        Shader(Shader &) = delete;
        Shader& operator=(Shader &) = delete;

        ~Shader();

        void setProjectionUniform(const Matrix4f &);
        void setViewUniform(const Matrix4f &);
        void setTexture0(const Texture &);

        void use();

    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
};

#endif
