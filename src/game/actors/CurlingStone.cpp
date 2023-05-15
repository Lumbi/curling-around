#include "CurlingStone.hpp"

#include "asset/AssetLibrary.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/components/PhysicsBodyComponent.hpp"

CurlingStone::CurlingStone()
{
    auto modelComponent = std::make_unique<ModelComponent>(
        AssetLibrary::shared().getModel(AssetLibrary::ModelKey::curlingStone),
        AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultCurlingStone)
    );

    auto physicsBodyComponent = std::make_unique<PhysicsBodyComponent>(
        PhysicsBody::makeSphere(1.0f, 100.0f)
    );

    attachComponent(std::move(modelComponent));
    attachComponent(std::move(physicsBodyComponent));
}

CurlingStone::~CurlingStone()
{}

PhysicsBodyComponent * CurlingStone::getPhysicsBodyComponent()
{
    // TODO: Avoid dynamic cast by keeping pointer
    for (auto&& component : getComponents()) {
        auto physicsBodyComponent = dynamic_cast<PhysicsBodyComponent*>(component.get());
        if (physicsBodyComponent) {
            return physicsBodyComponent;
        }
    }
    return nullptr;
}

PhysicsBody * CurlingStone::getBody()
{
    auto physicsBodyComponent = getPhysicsBodyComponent();
    if (physicsBodyComponent) {
        return &physicsBodyComponent->getBody();
    } else {
        return nullptr;
    }
}
