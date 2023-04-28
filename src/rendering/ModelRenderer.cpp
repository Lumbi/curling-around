#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"

#include "OpenGL.h"

#include "rendering/Mesh.hpp"

void ModelRenderer::render(const Model *model)
{
    if (model == nullptr) { return; }

    for (auto&& mesh : model->getMeshes()) {
        glBindVertexArray(mesh->vertexArray);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
