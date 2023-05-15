#include "Actor.hpp"

#include "Component.hpp"
#include "Scene.hpp"

Actor::Actor()
    : parent(nullptr)
{}

Actor::~Actor()
{}

Transform &Actor::getTransform()
{
    return transform;
}

Matrix4f Actor::getLocalToWorldMatrix()
{
    Matrix4f localToWorldMatrix = transform.getMatrix();
    Actor *nextParent = parent;
    while (nextParent) {
        localToWorldMatrix = localToWorldMatrix * nextParent->transform.getMatrix();
        nextParent = parent->parent;
    }
    return localToWorldMatrix;
}

Vector3f Actor::getWorldPosition()
{
    return getLocalToWorldMatrix() * transform.getPosition();
}

void Actor::update()
{
    for (auto&& component : components) {
        component->update();
    }
    for (auto&& child : children) {
        child->update();
    }
}

void Actor::draw(Scene &scene)
{
    for (auto&& component : components) {
        component->draw(scene);
    }
    for (auto&& child : children) {
        child->draw(scene);
    }
}

const std::vector<std::unique_ptr<Actor>>& Actor::getChildren() const
{
    return children;
}

void Actor::addChild(std::unique_ptr<Actor> actor)
{
    actor->parent = this;
    children.push_back(std::move(actor));
}

const std::vector<std::unique_ptr<Component>>& Actor::getComponents() const
{
    return components;
}

void Actor::attachComponent(std::unique_ptr<Component> component)
{
    component->setActor(this);
    components.push_back(std::move(component));
}

void Actor::detachComponent(Component *component)
{
    if (component == nullptr) return;
    component->setActor(nullptr);
    std::erase_if(components, [&] (auto&& c) { return c.get() == component; });
}
