#ifndef CURLING_STONE_H
#define CURLING_STONE_H

#include "game/Actor.hpp"

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

        /// @brief Get the physics body component of this curling stone.
        PhysicsBodyComponent * getPhysicsBodyComponent();

        /// @brief Get the physics body of the component of this curling stone.
        PhysicsBody * getBody();
};

#endif
