#include "Renderer.hpp"

#include "OpenGL.h"
#include <stack>

#include "Mesh.hpp"
#include "Model.hpp"
#include "Material.hpp"

Renderer::Renderer(SDL_Window *window, Camera *camera)
 : window(window), camera(camera)
{}

void Renderer::begin()
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Model &model, Material &material, const Matrix4f &transform)
{
    std::stack<Model::Node *> nodes;
    Model::Node *current = model.getRoot();
    nodes.push(current);
    while (!nodes.empty()) {
        Model::Node *top = nodes.top();
        nodes.pop();
        for (auto&& child : top->children) {
            nodes.push(child.get());
        }
        for (auto&& meshIndex : top->meshes) {
            auto mesh = model.getMeshAt(meshIndex);
            material.use(camera->getProjection(), camera->getView(), top->getModelMatrix() * transform);
            glBindVertexArray(mesh->vertexArray);
            glDrawElements(GL_TRIANGLES, GLsizei(mesh->indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

void Renderer::end()
{
    SDL_GL_SwapWindow(window);
}
