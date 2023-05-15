#include "ModelComponent.hpp"

#include "rendering/Camera.hpp"
#include "rendering/Material.hpp"
#include "game/Actor.hpp"
#include "game/Scene.hpp"

ModelComponent::ModelComponent(Model *model, Material *material)
    : model(model),
      material(material)
{}

ModelComponent::~ModelComponent()
{}

void ModelComponent::update()
{}

void ModelComponent::draw(Scene &scene)
{
    Actor *actor = getActor();
    if (model && material && actor) {
        renderer.render(
            *model,
            *material,
            scene.getCamera()->getProjection(),
            scene.getCamera()->getView(),
            actor->getLocalToWorldMatrix()
        );
    }
}
