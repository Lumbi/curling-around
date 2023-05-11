#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"
#include "rendering/Mesh.hpp"
#include "asset/ShaderLibrary.hpp"

#include "OpenGL.h"

void ModelRenderer::render(const Model &model, const Matrix4f &modelMatrix)
{
    Shader &shader = ShaderLibrary::instance().defaultShader;
    Model::Node *currentNode = model.getRoot();
    render(model, modelMatrix, *model.getRoot());
}

void ModelRenderer::render(const Model &model, const Matrix4f &modelMatrix, Model::Node &node)
{
    Shader &shader = ShaderLibrary::instance().defaultShader;

    for (auto&& meshIndex : node.meshes) {
        auto mesh = model.getMeshAt(meshIndex);

        shader.setModelUniform(node.getModelMatrix() * modelMatrix);

        glBindVertexArray(mesh->vertexArray);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    for (auto&& child : node.children) {
        render(model, modelMatrix, *child);
    }
}
