#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"
#include "rendering/Mesh.hpp"
#include "asset/ShaderLibrary.hpp"

#include "OpenGL.h"

void ModelRenderer::render(const Model &model, const Matrix4f &modelMatrix)
{
    Shader &shader = ShaderLibrary::instance().defaultShader;
    shader.setModelUniform(modelMatrix);

    Model::Node *currentNode = model.getRoot();

    render(model, *model.getRoot());
}

void ModelRenderer::render(const Model &model, Model::Node &node)
{
    Shader &shader = ShaderLibrary::instance().defaultShader;

    for (auto&& meshIndex : node.meshes) {
        auto mesh = model.getMeshAt(meshIndex);

        shader.setModelUniform(node.getModelTransform());

        glBindVertexArray(mesh->vertexArray);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    for (auto&& child : node.children) {
        render(model, *child);
    }
}
