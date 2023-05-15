#include "Scene.hpp"

#include "Actor.hpp"
#include "Component.hpp"
#include "rendering/Camera.hpp"

Scene::Scene()
    : root(std::make_unique<Actor>())
{}

Actor * Scene::getRoot()
{
    return root.get();
}

Camera * Scene::getCamera()
{
    return camera.get();
}

void Scene::setCamera(std::unique_ptr<Camera> camera)
{
    this->camera = std::move(camera);
}
