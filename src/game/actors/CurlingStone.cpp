#include "CurlingStone.hpp"

#include "game/Parameter.hpp"
#include "asset/AssetLibrary.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/components/PhysicsBodyComponent.hpp"

CurlingStone::CurlingStone(int playerID)
{
    auto modelComponent = std::make_unique<ModelComponent>(
        AssetLibrary::shared().getModel(AssetLibrary::ModelKey::curlingStone),
        playerID % 2 == 0
            ? AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultCurlingStoneRed)
            : AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultCurlingStoneBlue)
    );

    auto physicsBodyComponent = std::make_unique<PhysicsBodyComponent>(
        PhysicsBody::makeSphere(
            Parameter::shared().get(Parameter::Key::Actor_CurlingStone_Mass, 1.0f),
            100.0f
        )
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
