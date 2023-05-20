#include "ModelComponent.hpp"

#include "rendering/Camera.hpp"
#include "rendering/Material.hpp"
#include "rendering/Renderer.hpp"
#include "game/Actor.hpp"

ModelComponent::ModelComponent(Model *model, Material *material)
    : model(model),
      material(material)
{}

ModelComponent::~ModelComponent()
{}

void ModelComponent::update()
{}

void ModelComponent::draw(Renderer &renderer)
{
    Actor *actor = getActor();
    if (model && material && actor) {
        renderer.render(
            *model,
            *material,
            actor->getLocalToWorldMatrix()
        );
    }
}
