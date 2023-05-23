#ifndef PHYSICSBODY_COMPONENT_H
#define PHYSICSBODY_COMPONENT_H

#include "game/Component.hpp"
#include "physics/PhysicsBody.hpp"

#include <memory>

enum PhysicsBodyProperties: PhysicsBody::ID {
    freezing = 1 << 1,
    frozen = 1 << 2
};

class PhysicsBody;

/// @brief A component that handles updating and linking a physics body to an actor.
class PhysicsBodyComponent: public Component {
    public:
        /// @brief Initialize the physics body component.
        /// @param physicsBody The physics body to link the actor with.
        PhysicsBodyComponent(PhysicsBody physicsBody);

        /// @brief Destroy the physics body component.
        virtual ~PhysicsBodyComponent();

    public:
        /// @brief Update the physics body component for a single frame.
        virtual void update() override;

        /// @brief Draw the physics body component using the provided renderer (currently doesn't do anything but could be used for debug).
        virtual void draw(Renderer &) override;

        /// @brief The the physics body managed by the component.
        PhysicsBody& getBody();

        /// @brief Set the linear friction coefficient experienced by the physics body at each frame.
        void setFriction(float);

    private:
        PhysicsBody physicsBody;
        float friction = 0.02f;
};

#endif
