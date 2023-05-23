#ifndef CURLING_STONE_H
#define CURLING_STONE_H

#include "game/Actor.hpp"
#include "physics/PhysicsBody.hpp"

class ModelComponent;
class PhysicsBodyComponent;
class PhysicsBody;

/// @brief A curling stone thrown by players.
class CurlingStone: public Actor {
    public:
        /// @brief Initialize the curling stone.
        /// @param playerID The ID of the player owning the stone. This determines the color of the stone.
        explicit CurlingStone(int playerID);

        /// @brief Destroy the curling stone.
        virtual ~CurlingStone();

        /// @brief Get the physics body of the component of this curling stone.
        PhysicsBody * getBody();

        /// @brief Update the curling stone for a single frame.
        virtual void update() override;

        /// @brief Add a freezing effect to this curling stone.
        ///        When the stone touches another stone, it freezes it in place.
        void addFreezingEffect();

        /// @brief Remove the freezing effect.
        void removeFreezingEffect();

    private:
        using super = Actor;

        bool shouldFreeze = false;
        ModelComponent *freezingComponent = nullptr;

        void freeze();
};

#endif
