#include "Shader.hpp"

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "Texture.hpp"

#include <cstdio>

Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource)
{
   // Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint vertexShaderCompileStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
    if (!vertexShaderCompileStatus) {
        char vertexShaderCompileLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexShaderCompileLog);
        printf("Vertex shader compilation error: %s\n", vertexShaderCompileLog);
    }

    // Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint fragmentShaderCompileStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
    if (!fragmentShaderCompileStatus) {
        char fragmentShaderCompileLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentShaderCompileLog);
        printf("Fragment shader compilation error: %s\n", fragmentShaderCompileLog);
    }

    // Shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLint shaderProgramLinkStatus;

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramLinkStatus);
    if (!shaderProgramLinkStatus) {
        char shaderProgramLinkLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderProgramLinkLog);
        printf("Shader program link error: %s\n", shaderProgramLinkLog);
    }

    // Setup texture locations
    // TODO: Allow each shader to specify texture location
    use();
    glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}

void Shader::setProjectionUniform(const Matrix4f &projection)
{
    GLint projectionUniform = glGetUniformLocation(shaderProgram, "projection");
    glProgramUniformMatrix4fv(shaderProgram, projectionUniform, 1, GL_FALSE, projection.data);
}

void Shader::setViewUniform(const Matrix4f &view)
{
    GLint viewUniform = glGetUniformLocation(shaderProgram, "view");
    glProgramUniformMatrix4fv(shaderProgram, viewUniform, 1, GL_FALSE, view.data);
}

void Shader::setModelUniform(const Matrix4f &model)
{
    GLint modelUniform  = glGetUniformLocation(shaderProgram, "model");
    glProgramUniformMatrix4fv(shaderProgram, modelUniform, 1, GL_FALSE, model.data);
}

void Shader::setTexture0(const Texture &texture)
{
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
}

void Shader::setGlobalLightPosition(const Vector3f &globalLightPosition)
{
    GLint globalLightPositionUniform = glGetUniformLocation(shaderProgram, "globalLightPosition");
    glProgramUniform3fv(shaderProgram, globalLightPositionUniform, 1, (float*) &globalLightPosition);
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}
