#include "Scene.hpp"

#include "Actor.hpp"
#include "Component.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"

Scene::Scene()
    : root(std::make_unique<Actor>())
{}

Actor * Scene::getRoot()
{
    return root.get();
}

void Scene::update()
{
    root->update();
}

void Scene::draw(Renderer &renderer)
{
    root->draw(renderer);
}
