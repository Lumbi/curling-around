#include "Actor.hpp"

#include "Component.hpp"

Transform& Actor::getTransform()
{
    // TODO: Calculate world transform by walking up the hierarchy
    return transform;
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

void Actor::draw()
{
    for (auto&& component : components) {
        component->draw();
    }
    for (auto&& child : children) {
        child->draw();
    }
}

const std::vector<std::unique_ptr<Actor>>& Actor::getChildren() const
{
    return children;
}

void Actor::addChild(std::unique_ptr<Actor> actor)
{
    children.push_back(std::move(actor));
}

const std::vector<std::unique_ptr<Component>>& Actor::getComponents() const
{
    return components;
}

void Actor::attachComponent(std::unique_ptr<Component> component)
{
    component->setParent(this);
    components.push_back(std::move(component));
}

void Actor::detachComponent(Component *component)
{
    if (component == nullptr) return;
    component->setParent(nullptr);
    std::erase_if(components, [&] (auto&& c) { return c.get() == component; });
}
