#include "CurlingStone.hpp"

#include "asset/AssetLibrary.hpp"
#include "game/components/ModelComponent.hpp"
#include "game/components/PhysicsBodyComponent.hpp"

CurlingStone::CurlingStone()
{
    auto modelComponent = std::make_unique<ModelComponent>(
        AssetLibrary::shared().getModel(AssetLibrary::ModelKey::curlingStone)
    );

    auto physicsBodyComponent = std::make_unique<PhysicsBodyComponent>(
        PhysicsBody::makeSphere(1.0f, 1.0f)
    );

    attachComponent(std::move(modelComponent));
    attachComponent(std::move(physicsBodyComponent));
}

CurlingStone::~CurlingStone()
{}
