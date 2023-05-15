#ifndef PHYSICSBODY_COMPONENT_H
#define PHYSICSBODY_COMPONENT_H

#include "game/Component.hpp"
#include "physics/PhysicsBody.hpp"

#include <memory>

class PhysicsBody;

class PhysicsBodyComponent: public Component {
    public:
        PhysicsBodyComponent(PhysicsBody);
        virtual ~PhysicsBodyComponent();

    public:
        virtual void update() override;
        virtual void draw(Scene &) override;

        PhysicsBody& getBody();
        void setFriction(float);

    private:
        PhysicsBody physicsBody;
        float friction = 0.02f;
};

#endif
