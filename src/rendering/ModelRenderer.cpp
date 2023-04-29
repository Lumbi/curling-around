#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"
#include "rendering/Mesh.hpp"
#include "asset/ShaderLibrary.hpp"

#include "OpenGL.h"

void ModelRenderer::render(const Model &model, const Matrix4f &modelMatrix)
{
    Shader &shader = ShaderLibrary::instance().defaultShader;
    shader.setModelUniform(modelMatrix);

    for (auto&& mesh : model.getMeshes()) {
        glBindVertexArray(mesh->vertexArray);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
