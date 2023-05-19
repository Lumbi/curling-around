#include "Component.hpp"

#include "Actor.hpp"

Component::Component()
    : actor(nullptr)
{}

Component::~Component()
{}

void Component::setActor(Actor *newActor)
{
    this->actor = newActor;
}

Actor * Component::getActor() const
{
    return actor;
}
