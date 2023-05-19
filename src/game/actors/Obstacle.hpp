#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "math/Vector.hpp"
#include "game/Actor.hpp"

class PhysicsBodyComponent;
class PhysicsBody;

/// @brief An obstacle on the playing field.
class Obstacle: public Actor {
    public:
        /// @brief Initialize an obstacle.
        /// @param position The position of the obstacle.
        Obstacle(Vector3f position);

        /// @brief Destroy the obstacle.
        virtual ~Obstacle();
};

#endif
