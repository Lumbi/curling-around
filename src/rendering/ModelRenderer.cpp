#include "ModelRenderer.hpp"

#include "rendering/Model.hpp"

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

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
