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

    for (auto&& childToRemove : childrenToRemove) {
        std::erase_if(children, [&](auto&& child) { return child.get() == childToRemove; });
    }
    childrenToRemove.clear();

    for (auto&& componentToRemove: componentsToRemove) {
        std::erase_if(components, [&](auto&& component) { return component.get() == componentToRemove; });
    }
    componentsToRemove.clear();
}

void Actor::draw(Renderer &renderer)
{
    for (auto&& component : components) {
        component->draw(renderer);
    }

    for (auto&& child : children) {
        child->draw(renderer);
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

void Actor::removeChild(Actor *actor)
{
    if (!actor) { return; }
    if (actor->parent != this) { return; }
    actor->parent = nullptr;
    childrenToRemove.push_back(actor);
}

void Actor::removeFromParent()
{
    if (!parent) { return; }
    parent->removeChild(this);
}

const std::vector<std::unique_ptr<Component>>& Actor::getComponents() const
{
    return components;
}

void Actor::attachComponent(std::unique_ptr<Component> component)
{
    if (!component) return;
    component->setActor(this);
    components.push_back(std::move(component));
}

void Actor::detachComponent(Component *component)
{
    if (!component) { return; }
    componentsToRemove.push_back(component);
    component->setActor(nullptr);
}
