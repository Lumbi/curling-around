#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Material.hpp"

#include "OpenGL.h"

void ModelRenderer::render(
    const Model &model,
    const Material &material,
    const Matrix4f &projectionMatrix,
    const Matrix4f &viewMatrix,
    const Matrix4f &modelMatrix
)
{
    Model::Node *currentNode = model.getRoot();
    render(model, material, projectionMatrix, viewMatrix, modelMatrix, *model.getRoot());
}

void ModelRenderer::render(
    const Model &model,
    const Material &material,
    const Matrix4f &projectionMatrix,
    const Matrix4f &viewMatrix,
    const Matrix4f &modelMatrix,
    Model::Node &node
)
{
    for (auto&& meshIndex : node.meshes) {
        auto mesh = model.getMeshAt(meshIndex);

        material.use(projectionMatrix, viewMatrix, node.getModelMatrix() * modelMatrix);

        glBindVertexArray(mesh->vertexArray);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    for (auto&& child : node.children) {
        render(model, material, projectionMatrix, viewMatrix, modelMatrix, *child);
    }
}
