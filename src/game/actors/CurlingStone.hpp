#ifndef CURLING_STONE_H
#define CURLING_STONE_H

#include "game/Actor.hpp"

class PhysicsBodyComponent;
class PhysicsBody;

class CurlingStone: public Actor {
    public:
        CurlingStone();

        virtual ~CurlingStone();

    public:
        PhysicsBodyComponent * getPhysicsBodyComponent();
        PhysicsBody * getBody();
};

#endif
