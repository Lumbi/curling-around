#include "Component.hpp"

#include "Actor.hpp"

Component::Component()
    : parent(nullptr)
{}

Component::~Component()
{}

void Component::setParent(Actor *actor)
{
    parent = actor;
}

Actor * const Component::getParent() const
{
    return parent;
}
