#include "Scene.hpp"

#include "Actor.hpp"
#include "Component.hpp"

Scene::Scene()
    : root(std::make_unique<Actor>())
{}

Actor * const Scene::getRoot()
{
    return root.get();
}
