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
    if (model) {
        renderer.render(*model, getParent()->getTransform().getMatrix());
    }
}
