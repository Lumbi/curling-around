#include "ShaderLibrary.hpp"

const char *DEFAULT_VERTEX_SHADER_SOURCE = R"(
    #version 410 core

    layout (location = 0) in vec3 attribPosition;
    layout (location = 1) in vec3 attribNormal;
    layout (location = 2) in vec2 attribTexCoord0;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    out vec3 position;
    out vec3 normal;
    out vec2 textCoord0;

    void main() {
        gl_Position = projection * view * model * vec4(attribPosition, 1.0f);

        position = (model * vec4(attribPosition, 1.0)).xyz;
        normal = normalize((model * vec4(attribNormal, 0.0f)).xyz);
        textCoord0 = attribTexCoord0;
    }
)";

const char *DEFAULT_FRAGMENT_SHADER_SOURCE = R"(
    #version 410 core

    in vec3 position;
    in vec3 normal;
    in vec2 textCoord0;

    uniform vec3 globalLightPosition;
    uniform sampler2D texture0;

    out vec4 fragmentColor;

    void main() {
        // Texture color
        vec4 textureColor0 = texture(texture0, textCoord0);

        // Ambient light
        vec3 ambientLightColor = vec3(0.9f, 0.9f, 1.0f); // blueish
        float ambientLightStrength = 0.2f;
        vec3 ambientLight = ambientLightStrength * ambientLightColor;

        // Global diffuse light
        vec3 globalLightDirection = normalize(globalLightPosition - position);
        float globalLightDiffuse = max(dot(normal, globalLightDirection), 0.0);

        // Apply lighting
        vec3 litColor = textureColor0.rgb;
        litColor *= (ambientLight + globalLightDiffuse);

        fragmentColor = vec4(litColor, textureColor0.a); // Restore opacity
    }
)";

const char *EFFECT_VERTEX_SHADER_SOURCE = R"(
    #version 410 core

    layout (location = 0) in vec3 attribPosition;
    layout (location = 1) in vec3 attribNormal;
    layout (location = 2) in vec2 attribTexCoord0;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
    uniform float time;

    out vec2 textCoord0;
    out float interpolation;

    void main() {
        vec3 normal = normalize((model * vec4(attribNormal, 0.0f)).xyz);

        float adjustedTime = 3.f * time;
        interpolation = sin(adjustedTime) * sin(adjustedTime);
        vec4 displacement = 20.f * vec4(normal, 0.f) * (0.1f + interpolation);
        gl_Position = projection * view * (model * vec4(attribPosition, 1.0f) + displacement);

        textCoord0 = attribTexCoord0;
    }
)";

const char *EFFECT_FRAGMENT_SHADER_SOURCE = R"(
    #version 410 core

    in float interpolation;
    in vec2 textCoord0;

    uniform vec3 globalLightPosition;
    uniform sampler2D texture0;

    out vec4 fragmentColor;

    void main() {
        vec4 textureColor0 = texture(texture0, textCoord0);
        fragmentColor = vec4(textureColor0.rgb, 0.75f * (1.f - interpolation)); // Transparency
    }
)";

ShaderLibrary & ShaderLibrary::shared()
{
    static ShaderLibrary instance;
    return instance;
}

ShaderLibrary::ShaderLibrary()
    : defaultShader(DEFAULT_VERTEX_SHADER_SOURCE, DEFAULT_FRAGMENT_SHADER_SOURCE),
      effectShader(EFFECT_VERTEX_SHADER_SOURCE, EFFECT_FRAGMENT_SHADER_SOURCE)
{}
