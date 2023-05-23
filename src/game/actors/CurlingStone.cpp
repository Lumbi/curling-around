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

    PhysicsBody body = PhysicsBody::makeSphere(
        Parameter::shared().get(Parameter::Key::Actor_CurlingStone_Mass, 1.0f),
        100.0f
    );
    body.bounciness = Parameter::shared().get(Parameter::Key::Actor_CurlingStone_Bounciness, 1.0f);

    auto physicsBodyComponent = std::make_unique<PhysicsBodyComponent>(body);

    attachComponent(std::move(modelComponent));
    attachComponent(std::move(physicsBodyComponent));
}

CurlingStone::~CurlingStone()
{}

PhysicsBody * CurlingStone::getBody()
{
    auto physicsBodyComponent = getComponent<PhysicsBodyComponent>();
    if (physicsBodyComponent) {
        return &physicsBodyComponent->getBody();
    } else {
        return nullptr;
    }
}
