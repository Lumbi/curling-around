#include "ShaderLibrary.hpp"

const char *DEFAULT_VERTEX_SHADER_SOURCE = R"(
    #version 410 core

    layout (location = 0) in vec3 attribPosition;
    layout (location = 1) in vec3 attribNormal;

    uniform mat4 projection;
    uniform mat4 view;

    out vec3 position;
    out vec3 normal;

    void main() {
        gl_Position = projection * view * vec4(attribPosition, 1.0f);

        position = attribPosition;
        normal = attribNormal;
    }
)";

const char *DEFAULT_FRAGMENT_SHADER_SOURCE = R"(
    #version 410 core

    in vec3 position;
    in vec3 normal;

    uniform vec3 globalLightPosition;

    out vec4 fragmentColor;

    void main() {
        vec3 color = vec3(0.1f, 0.3f, 0.6f);

        // Ambient light
        vec3 ambientLightColor = vec3(1.0f, 1.0f, 1.0f);
        float ambientLightStrength = 0.5f;
        vec3 ambientLight = ambientLightStrength * ambientLightColor;

        // Global light diffuse
        vec3 globalLightDirection = normalize(globalLightPosition - position);
        float globalLightDiffuse = max(dot(normal, globalLightDirection), 0.0);

        color *= (ambientLight + globalLightDiffuse);
        fragmentColor = vec4(color, 1.0f);
    }
)";

ShaderLibrary::ShaderLibrary()
    : defaultShader(DEFAULT_VERTEX_SHADER_SOURCE, DEFAULT_FRAGMENT_SHADER_SOURCE)
{}
