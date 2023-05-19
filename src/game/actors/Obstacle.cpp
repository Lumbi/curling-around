#include "Obstacle.hpp"

#include "asset/AssetLibrary.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/components/PhysicsBodyComponent.hpp"

Obstacle::Obstacle(Vector3f position)
{
    auto modelComponent = std::make_unique<ModelComponent>(
        AssetLibrary::shared().getModel(AssetLibrary::ModelKey::rock),
        AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultIce)
    );

    auto physicsBodyComponent = std::make_unique<PhysicsBodyComponent>(
        PhysicsBody::makeSphere(1.0f, 150.0f)
    );
    physicsBodyComponent->getBody().position = position;
    physicsBodyComponent->getBody().type = PhysicsBody::Type::fixed;
    getTransform().setRotation({ 0.f, (rand() % 360) * (float)M_PI / 180.f, 0.f }); // TODO: Support physics body rotation

    attachComponent(std::move(modelComponent));
    attachComponent(std::move(physicsBodyComponent));
}

Obstacle::~Obstacle()
{}
