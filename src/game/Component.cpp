#include "Component.hpp"

#include "Actor.hpp"

Component::Component()
    : actor(nullptr)
{}

Component::~Component()
{}

void Component::setActor(Actor *actor)
{
    this->actor = actor;
}

Actor * const Component::getActor() const
{
    return actor;
}
