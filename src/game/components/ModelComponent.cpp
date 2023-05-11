#include "ModelComponent.hpp"

#include "game/Actor.hpp"

ModelComponent::ModelComponent(Model *model)
    : model(model)
{}

ModelComponent::~ModelComponent()
{}

void ModelComponent::update()
{}

void ModelComponent::draw()
{
    Actor *actor = getActor();
    if (model && actor) {
        renderer.render(*model, actor->getLocalToWorldMatrix());
    }
}
