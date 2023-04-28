#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

class Matrix4f;

class Shader
{
    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        Shader(Shader &) = delete;
        Shader& operator=(Shader &) = delete;

        ~Shader();

        void setProjectionUniform(const Matrix4f &);
        void setViewUniform(const Matrix4f &);

        void use();

    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
};

#endif
