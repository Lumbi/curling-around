#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "math/Vector.hpp"
#include "game/Actor.hpp"

class PhysicsBodyComponent;
class PhysicsBody;

class Obstacle: public Actor {
    public:
        Obstacle(Vector3f position);

        virtual ~Obstacle();
};

#endif
