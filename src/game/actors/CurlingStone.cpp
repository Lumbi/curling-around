#include "CurlingStone.hpp"

#include "game/Parameter.hpp"
#include "asset/AssetLibrary.hpp"
#include "physics/Physics.hpp"
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

void CurlingStone::update()
{
    super::update();

    // Check for collisions with "freezing" bodies
    PhysicsBody *body = getBody();
    if (!body) { return; }
    auto contacts = Physics::shared().getContacts(body->id);
    for (auto&& otherBody : contacts) {
        if (!otherBody) { continue; }

        // Case: this is getting frozen
        if (
            !(body->tag & PhysicsBodyProperties::frozen) &&
            (otherBody->tag & PhysicsBodyProperties::freezing)
        ) {
            freeze();
        }

        // Case: this is freezing other
        else if (
            (body->tag & PhysicsBodyProperties::freezing) &&
            !(otherBody->tag & PhysicsBodyProperties::frozen)
        ) {
            removeFreezingEffect();
        }
    }
}

void CurlingStone::addFreezingEffect()
{
    PhysicsBody *body = getBody();
    if (!body) { return; }
    body->tag |= PhysicsBodyProperties::freezing;
}

void CurlingStone::removeFreezingEffect()
{
    PhysicsBody *body = getBody();
    if (!body) { return; }
    body->tag ^= PhysicsBodyProperties::freezing;
}

void CurlingStone::freeze()
{
    auto modelComponent = std::make_unique<ModelComponent>(
        AssetLibrary::shared().getModel(AssetLibrary::ModelKey::frozen),
        AssetLibrary::shared().getMaterial(AssetLibrary::MaterialKey::defaultIce)
    );
    attachComponent(std::move(modelComponent));

    PhysicsBody *body = getBody();
    if (body) {
        body->type = PhysicsBody::fixed;
        body->velocity = Vector3f::zero;
    }
}
